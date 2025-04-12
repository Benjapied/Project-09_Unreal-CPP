// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EPC_CharacterBase.h"
#include "EPUI_Combat.h"
#include "Animation/AnimMontage.h"
#include "EPC_NPC.generated.h"

UCLASS()
class ENTERTHEPOTATO_API AEPC_NPC : public AEPC_CharacterBase
{
	GENERATED_BODY()

public:

	AEPC_NPC();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UBehaviorTree* GetBehaviorTree() const;

	float GetMinAttackRange() const;

	float GetMaxAttackRange() const;

	//int Attack_Implementation(UEP_AttackType type) override;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AI, meta=(AllowPrivateAccess="true"))
	UBehaviorTree* Tree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
	float MinAttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
	float MaxAttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AEP_BaseWeapon> m_weaponType;

};
