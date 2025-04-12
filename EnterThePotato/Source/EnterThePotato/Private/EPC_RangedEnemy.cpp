#include "EPC_RangedEnemy.h"
#include "EPA_Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Consts.h"

AEPC_RangedEnemy::AEPC_RangedEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEPC_RangedEnemy::BeginPlay()
{
	Super::BeginPlay();

	//AttachWeaponMesh();
}

void AEPC_RangedEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEPC_RangedEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

//void AEPC_RangedEnemy::AttackStart_Implementation()
//{
//	Super::AttackStart_Implementation();
//	//SpawnProjectile();
//}

void AEPC_RangedEnemy::SpawnProjectile()
{
	if (!ProjectileDataAsset) return;

	FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.0f;
	FRotator SpawnRotation = GetActorRotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	AEPA_Projectile* SpawnedProjectile = GetWorld()->SpawnActor<AEPA_Projectile>(AEPA_Projectile::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);

	if (SpawnedProjectile)
	{
		SpawnedProjectile->InitializeFromDataAsset(ProjectileDataAsset);
	}
}

void AEPC_RangedEnemy::AttachWeaponMesh()
{
	if (!WeaponMesh) return;

	if (!WeaponMeshComponent)
	{
		WeaponMeshComponent = NewObject<UStaticMeshComponent>(this);
		WeaponMeshComponent->RegisterComponent();
		WeaponMeshComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, defs::RightFistSocketName);
	}

	WeaponMeshComponent->SetStaticMesh(WeaponMesh);

	WeaponMeshComponent->SetRelativeLocation({-30, 0, 0});
	WeaponMeshComponent->SetRelativeRotation(FRotator::ZeroRotator);
}
