// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "EPI_CanReceiveDamage.h"
#include "Components/BoxComponent.h"

#include "EPI_LifeInterface.h"

#include "EP_Poutch.generated.h"

UCLASS()
class ENTERTHEPOTATO_API AEP_Poutch : public AActor, public IEPI_LifeInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEP_Poutch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float GetHealth() override;
	float GetMaxHealth() override;
	void SetHealth(float NewHealth) override;
	void TakeDamage(float damage) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* m_cube;

	float Health;
	float MaxHealth;

	UFUNCTION()
	void SwordOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

};
