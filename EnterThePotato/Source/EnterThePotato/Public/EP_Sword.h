// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "./../EP_BaseWeapon.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "EP_Sword.generated.h"

/**
 * 
 */
UCLASS()
class ENTERTHEPOTATO_API AEP_Sword : public AEP_BaseWeapon
{
	GENERATED_BODY()
	
public:

	AEP_Sword();

	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	void OnActivateWeapon(AActor* aactor) override;
	void OnDesactivateWeapon() override;

	UFUNCTION()
	void SwordOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* m_swordMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* m_cube;

};
