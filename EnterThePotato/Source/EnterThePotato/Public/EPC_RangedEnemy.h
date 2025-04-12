#pragma once

#include "CoreMinimal.h"
#include "EPC_NPC.h"
#include "EPDA_Projectile.h" 
#include "EPC_RangedEnemy.generated.h"

/**
 * 
 */
UCLASS()
class ENTERTHEPOTATO_API AEPC_RangedEnemy : public AEPC_NPC
{
	GENERATED_BODY()

public:

	AEPC_RangedEnemy();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//void AttackStart_Implementation() override;

protected:

	virtual void BeginPlay() override;

	UPROPERTY()
	UStaticMeshComponent* WeaponMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UStaticMesh* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Settings")
	UEPDA_Projectile* ProjectileDataAsset;

	void SpawnProjectile();
	void AttachWeaponMesh();

};
