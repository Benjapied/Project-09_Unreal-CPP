#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EPUI_WaveEventInterface.h"
#include "EPA_WaveSpawner.generated.h"

USTRUCT(BlueprintType)
struct FEnemyWaveData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Wave")
    FString Type;

    UPROPERTY(BlueprintReadWrite, Category = "Wave")
    int32 Count;
};

USTRUCT(BlueprintType)
struct FWaveData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Wave")
    int32 WaveNumber;

    UPROPERTY(BlueprintReadWrite, Category = "Wave")
    float SpawnInterval;

    UPROPERTY(BlueprintReadWrite, Category = "Wave")
    TArray<FEnemyWaveData> Enemies;
};

UCLASS()
class ENTERTHEPOTATO_API AEPA_WaveSpawner : public AActor
{
    GENERATED_BODY()

public:
    AEPA_WaveSpawner();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Wave")
    int32 GetEnemiesRemaining() const { return EnemiesRemaining; }

protected:
    void LoadWaveData();
    void StartWave(int WaveIndex);
    void SpawnEnemies(const FEnemyWaveData& EnemyData);

    UFUNCTION()
    void OnEnemyKilled(AActor* DestroyedActor);

    void OnWaveStarted();
    void OnWaveCompleted();
    void StartNextWave();

    int RetryCount;
    const int MaxRetries = 5;
    FTimerHandle WaveRetryTimerHandle;

    FVector GetRandomSpawnLocation();

    UPROPERTY(EditDefaultsOnly, Category = "Wave")
    TSubclassOf<AActor> EnemyTypeAClass;

    UPROPERTY(EditDefaultsOnly, Category = "Wave")
    TSubclassOf<AActor> EnemyTypeBClass;

    UPROPERTY(EditAnywhere, Category = "Wave")
    float MinSpawnDistance = 500.0f;

    UPROPERTY(EditAnywhere, Category = "Wave")
    float MaxSpawnDistance = 1000.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Wave", meta = (AllowPrivateAccess = "true"))
    int32 EnemiesRemaining;
    int32 TotalEnemiesInWave;

    int32 CurrentWaveIndex;
    FTimerHandle WaveTimerHandle;
    TArray<FWaveData> WaveData;
};
