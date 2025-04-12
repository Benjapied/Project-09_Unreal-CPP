// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EPC_NPC.h"
#include "EPC_ContactEnemy.generated.h"

/**
 * 
 */
UCLASS()
class ENTERTHEPOTATO_API AEPC_ContactEnemy : public AEPC_NPC
{
	GENERATED_BODY()

public:

	AEPC_ContactEnemy();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//void AttackStart_Implementation() override;
	//void AttackEnd_Implementation() override;
	
protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* RightFistCollisionBox;
};
