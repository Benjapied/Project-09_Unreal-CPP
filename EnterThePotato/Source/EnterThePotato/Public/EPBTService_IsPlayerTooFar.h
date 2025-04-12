// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "EPBTService_IsPlayerTooFar.generated.h"

/**
 * 
 */
UCLASS()
class ENTERTHEPOTATO_API UEPBTService_IsPlayerTooFar : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:

	UEPBTService_IsPlayerTooFar();
	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
