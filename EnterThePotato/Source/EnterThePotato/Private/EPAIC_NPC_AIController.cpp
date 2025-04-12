// Fill out your copyright notice in the Description page of Project Settings.


#include "EPAIC_NPC_AIController.h"
#include "EPC_NPC.h"

AEPAIC_NPC_AIController::AEPAIC_NPC_AIController(FObjectInitializer const& ObjectInitializer)
{
}

void AEPAIC_NPC_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (AEPC_NPC* const npc = Cast< AEPC_NPC>(InPawn))
	{
		if (UBehaviorTree* const tree = npc->GetBehaviorTree())
		{
			UBlackboardComponent* blackboard;
			UseBlackboard(tree->BlackboardAsset, blackboard);
			Blackboard = blackboard;
			RunBehaviorTree(tree);
		}
	}
}
