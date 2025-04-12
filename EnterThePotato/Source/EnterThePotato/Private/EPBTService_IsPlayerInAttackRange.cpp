// Fill out your copyright notice in the Description page of Project Settings.


#include "EPBTService_IsPlayerInAttackRange.h"
#include "EPAIC_NPC_AIController.h"
#include "EPC_NPC.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"

UEPBTService_IsPlayerInAttackRange::UEPBTService_IsPlayerInAttackRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Player In Attack Range");
}

void UEPBTService_IsPlayerInAttackRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AEPAIC_NPC_AIController const* const cont = Cast<AEPAIC_NPC_AIController>(OwnerComp.GetAIOwner());
    if (!cont) return;

    AEPC_NPC const* const npc = Cast<AEPC_NPC>(cont->GetPawn());
    if (!npc) return;

    ACharacter const* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (!player) return;

    float CurrentMinAttackRange = npc->GetMinAttackRange();
    float CurrentMaxAttackRange = npc->GetMaxAttackRange();

    bool bIsInMeleeRange = npc->GetDistanceTo(player) <= CurrentMaxAttackRange && npc->GetDistanceTo(player) >= CurrentMinAttackRange;
    OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), bIsInMeleeRange);
}
