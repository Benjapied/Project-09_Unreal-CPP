// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EP_CrossbowProjectile.generated.h"

UCLASS()
class ENTERTHEPOTATO_API AEP_CrossbowProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEP_CrossbowProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	AActor* m_owner;

	UPROPERTY()
	float m_lifeTime;
	float m_currentLifeTime;
	float m_damage;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void InitProjectileComponent();

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* m_projectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* m_projectileStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UProjectileMovementComponent* m_projectileComponent;


	void InitProjectile(AActor* actor, float damage);

};
