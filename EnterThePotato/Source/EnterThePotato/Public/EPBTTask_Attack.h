// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "EPC_NPC.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EPBTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class ENTERTHEPOTATO_API UEPBTTask_Attack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:

	UEPBTTask_Attack();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:

	bool MontageHasFinished(AEPC_NPC* const npc);
};
