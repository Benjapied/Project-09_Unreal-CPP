// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "EPBTTask_MoveAwayFromPlayer.generated.h"

/**
 * 
 */
UCLASS()
class ENTERTHEPOTATO_API UEPBTTask_MoveAwayFromPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:

	UEPBTTask_MoveAwayFromPlayer(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
