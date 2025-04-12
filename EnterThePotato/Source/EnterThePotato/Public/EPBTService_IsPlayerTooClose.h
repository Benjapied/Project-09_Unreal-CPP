// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "EPBTService_IsPlayerTooClose.generated.h"

/**
 * 
 */
UCLASS()
class ENTERTHEPOTATO_API UEPBTService_IsPlayerTooClose : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:

	UEPBTService_IsPlayerTooClose();
	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
