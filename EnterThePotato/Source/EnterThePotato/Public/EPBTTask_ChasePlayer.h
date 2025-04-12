// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "EPBTTask_ChasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class ENTERTHEPOTATO_API UEPBTTask_ChasePlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:

	explicit UEPBTTask_ChasePlayer(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
