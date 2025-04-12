#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EPA_Projectile.generated.h"

UCLASS()
class ENTERTHEPOTATO_API AEPA_Projectile : public AActor
{
	GENERATED_BODY()
	
public:

	AEPA_Projectile();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* ProjectileComponent;

	UFUNCTION(BlueprintCallable, Category = "Initialization")
	void InitializeFromDataAsset(class UEPDA_Projectile* DataAsset);

	UPROPERTY(BlueprintReadOnly)
	float Damage;

	UFUNCTION()
	void OnProjectileOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

};
