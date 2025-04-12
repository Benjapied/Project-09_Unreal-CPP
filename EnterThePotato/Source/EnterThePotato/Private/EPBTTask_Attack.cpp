// Fill out your copyright notice in the Description page of Project Settings.


#include "EPBTTask_Attack.h"
#include "EPUI_Combat.h"
#include "EPAIC_NPC_AIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"

UEPBTTask_Attack::UEPBTTask_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UEPBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	bool const OutOfRange = !OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
	if (OutOfRange)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	AAIController const* const cont = OwnerComp.GetAIOwner();
	AEPC_NPC* const npc = Cast<AEPC_NPC>(cont->GetPawn());

	if (IEPUI_Combat* const icombat = Cast<IEPUI_Combat>(npc))
	{
		if (MontageHasFinished(npc))
		{
			icombat->Execute_Attack(npc, UEP_AttackType::BaseAttack);
		}
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Type();
}

bool UEPBTTask_Attack::MontageHasFinished(AEPC_NPC* const npc)
{
	return npc->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(npc->GetMontage());
}
