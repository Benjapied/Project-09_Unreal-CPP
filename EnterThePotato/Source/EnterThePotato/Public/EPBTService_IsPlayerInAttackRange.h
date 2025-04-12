// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "EPBTService_IsPlayerInAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class ENTERTHEPOTATO_API UEPBTService_IsPlayerInAttackRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:

	UEPBTService_IsPlayerInAttackRange();
	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
