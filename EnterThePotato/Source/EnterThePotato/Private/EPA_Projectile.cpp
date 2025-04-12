#include "EPA_Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "EPDA_Projectile.h"
#include "EPC_CharacterBase.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h" 

AEPA_Projectile::AEPA_Projectile()
{
    PrimaryActorTick.bCanEverTick = false;

    ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
    RootComponent = ProjectileMesh;

    ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    ProjectileMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    ProjectileMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
    ProjectileMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Component"));
    ProjectileComponent->InitialSpeed = 800;
    ProjectileComponent->MaxSpeed = 8500;
    ProjectileComponent->ProjectileGravityScale = 0;

    InitialLifeSpan = 5.0f;
}


void AEPA_Projectile::InitializeFromDataAsset(UEPDA_Projectile* DataAsset)
{
    if (DataAsset)
    {
        if (DataAsset->GetProjectileMesh())
        {
            ProjectileMesh->SetStaticMesh(DataAsset->GetProjectileMesh());
        }

        ProjectileComponent->InitialSpeed = DataAsset->GetInitialSpeed();
        ProjectileComponent->MaxSpeed = DataAsset->GetMaxSpeed();
        ProjectileComponent->ProjectileGravityScale = DataAsset->GetGravityScale();
        Damage = DataAsset->GetDamage();
    }
}

void AEPA_Projectile::BeginPlay()
{
    Super::BeginPlay();
    
    ProjectileMesh->OnComponentBeginOverlap.AddDynamic(this, &AEPA_Projectile::OnProjectileOverlap);
}

void AEPA_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEPA_Projectile::OnProjectileOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this)
    {
        APawn* HitPawn = Cast<APawn>(OtherActor);
        if (HitPawn && HitPawn->IsPlayerControlled())
        {
            if (AEPC_CharacterBase* const Opponent = Cast<AEPC_CharacterBase>(OtherActor))
            {
                float NewHealth = Opponent->GetHealth() - Damage;
                Opponent->SetHealth(NewHealth);
            }
            
            Destroy();
        }
    }
}


