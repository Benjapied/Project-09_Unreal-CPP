#include "EPA_WaveSpawner.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "JsonObjectConverter.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "EPC_CharacterBase.h"
#include "EPGS_ArenaGameState.h"

AEPA_WaveSpawner::AEPA_WaveSpawner()
{
    PrimaryActorTick.bCanEverTick = true;
    CurrentWaveIndex = 0;
    EnemiesRemaining = 0;

    RootComponent = CreateDefaultSubobject<USceneComponent>("Scene Component");
}

void AEPA_WaveSpawner::BeginPlay()
{
    Super::BeginPlay();
    LoadWaveData();
    StartWave(CurrentWaveIndex);
}

void AEPA_WaveSpawner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AEPA_WaveSpawner::LoadWaveData()
{
    FString FilePath = FPaths::ProjectContentDir() + "WaveData.json";
    FString FileContent;

    if (FFileHelper::LoadFileToString(FileContent, *FilePath))
    {
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(FileContent);

        if (FJsonSerializer::Deserialize(Reader, JsonObject))
        {
            const TArray<TSharedPtr<FJsonValue>> WavesArray = JsonObject->GetArrayField("waves");
            for (const TSharedPtr<FJsonValue>& WaveValue : WavesArray)
            {
                FWaveData NewWave;
                TSharedPtr<FJsonObject> WaveObject = WaveValue->AsObject();

                NewWave.WaveNumber = WaveObject->GetIntegerField("waveNumber");
                NewWave.SpawnInterval = WaveObject->GetNumberField("spawnInterval");

                const TArray<TSharedPtr<FJsonValue>> EnemiesArray = WaveObject->GetArrayField("enemies");
                for (const TSharedPtr<FJsonValue>& EnemyValue : EnemiesArray)
                {
                    FEnemyWaveData NewEnemy;
                    TSharedPtr<FJsonObject> EnemyObject = EnemyValue->AsObject();

                    NewEnemy.Type = EnemyObject->GetStringField("type");
                    NewEnemy.Count = EnemyObject->GetIntegerField("count");

                    NewWave.Enemies.Add(NewEnemy);
                }

                WaveData.Add(NewWave);
            }
        }
    }
}

void AEPA_WaveSpawner::StartWave(int WaveIndex)
{
    if (WaveData.IsValidIndex(WaveIndex))
    {
        UE_LOG(LogTemp, Warning, TEXT("Starting wave %d (Retry %d)"), WaveIndex, RetryCount);

        EnemiesRemaining = 0;
        TotalEnemiesInWave = 0;

        OnWaveStarted();

        const FWaveData& CurrentWave = WaveData[WaveIndex];
        for (const FEnemyWaveData& Enemy : CurrentWave.Enemies)
        {
            SpawnEnemies(Enemy);
        }

        if (EnemiesRemaining == 0)
        {
            RetryCount++;
            if (RetryCount <= MaxRetries)
            {
                UE_LOG(LogTemp, Warning, TEXT("No enemies were spawned for wave %d. Retrying... (Attempt %d/%d)"), WaveIndex, RetryCount, MaxRetries);
                GetWorld()->GetTimerManager().ClearTimer(WaveRetryTimerHandle);
                GetWorld()->GetTimerManager().SetTimer(WaveRetryTimerHandle, [this, WaveIndex]()
                    {
                        StartWave(WaveIndex);
                    }, 0.5f, false);
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to spawn wave %d after %d attempts."), WaveIndex, MaxRetries);
                RetryCount = 0;
                OnWaveCompleted();
            }
        }
        else
        {
            RetryCount = 0;
        }
    }
}


void AEPA_WaveSpawner::SpawnEnemies(const FEnemyWaveData& EnemyData)
{
    if (!GetWorld()) return;

    TSubclassOf<AActor> EnemyClass = nullptr;

    if (EnemyData.Type == "EnemyTypeA" && EnemyTypeAClass)
    {
        EnemyClass = EnemyTypeAClass;
    }
    else if (EnemyData.Type == "EnemyTypeB" && EnemyTypeBClass)
    {
        EnemyClass = EnemyTypeBClass;
    }

    if (!EnemyClass)
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid EnemyClass for type %s"), *EnemyData.Type);
        return;
    }

    ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (!PlayerCharacter)
    {
        UE_LOG(LogTemp, Error, TEXT("No player character found!"));
        return;
    }

    FVector PlayerLocation = PlayerCharacter->GetActorLocation();
    UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

    if (!NavSystem)
    {
        UE_LOG(LogTemp, Error, TEXT("Navigation System is NULL!"));
        return;
    }

    for (int i = 0; i < EnemyData.Count; ++i)
    {
        FVector SpawnLocation;
        bool bFoundValidLocation = false;

        for (int Attempts = 0; Attempts < 10; ++Attempts)
        {
            FVector RandomPoint = PlayerLocation + UKismetMathLibrary::RandomUnitVector() * FMath::RandRange(MinSpawnDistance, MaxSpawnDistance);
            FNavLocation NavLocation;

            if (NavSystem->GetRandomPointInNavigableRadius(RandomPoint, 1000.f, NavLocation))
            {
                SpawnLocation = NavLocation.Location;
                bFoundValidLocation = true;
                break;
            }
        }

        if (bFoundValidLocation)
        {
            AActor* SpawnedEnemy = GetWorld()->SpawnActor<AActor>(EnemyClass, SpawnLocation, FRotator::ZeroRotator);
            if (!SpawnedEnemy)
            {
                UE_LOG(LogTemp, Warning, TEXT("Failed to spawn enemy"));
            }
            else
            {
                EnemiesRemaining++;
                TotalEnemiesInWave++;
                SpawnedEnemy->OnDestroyed.AddDynamic(this, &AEPA_WaveSpawner::OnEnemyKilled);
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to find valid spawn location for enemy %s"), *EnemyData.Type);
        }
    }
}

FVector AEPA_WaveSpawner::GetRandomSpawnLocation()
{
    FVector Origin = GetActorLocation();
    float Radius = 500.0f;
    return UKismetMathLibrary::RandomPointInBoundingBox(Origin, FVector(Radius, Radius, 0.0f));
}

void AEPA_WaveSpawner::OnEnemyKilled(AActor* DestroyedActor)
{
    EnemiesRemaining--;

    AEPGS_ArenaGameState* GameState = GetWorld()->GetGameState<AEPGS_ArenaGameState>();
    if (GameState)
    {
        GameState->UpdateWaveProgress(EnemiesRemaining, TotalEnemiesInWave);
    }

    if (EnemiesRemaining <= 0)
    {
        OnWaveCompleted();
    }
}

void AEPA_WaveSpawner::OnWaveStarted()
{
    AEPGS_ArenaGameState* GameState = GetWorld()->GetGameState<AEPGS_ArenaGameState>();
    if (GameState)
    {
        GameState->OnWaveStarted(CurrentWaveIndex);
    }
}

void AEPA_WaveSpawner::OnWaveCompleted()
{
    UE_LOG(LogTemp, Warning, TEXT("Wave %d completed!"), CurrentWaveIndex);

    AEPGS_ArenaGameState* GameState = GetWorld()->GetGameState<AEPGS_ArenaGameState>();
    if (GameState)
    {
        GameState->OnWaveFinished(CurrentWaveIndex);
    }

    GetWorld()->GetTimerManager().SetTimer(WaveTimerHandle, this, &AEPA_WaveSpawner::StartNextWave, WaveData[CurrentWaveIndex].SpawnInterval, false);
}

void AEPA_WaveSpawner::StartNextWave()
{
    ++CurrentWaveIndex;
    if (WaveData.IsValidIndex(CurrentWaveIndex))
    {
        StartWave(CurrentWaveIndex);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("All waves completed!"));
    }
}
