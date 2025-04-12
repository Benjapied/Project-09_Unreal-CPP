#include "EPBTService_IsPlayerTooClose.h"
#include "EPAIC_NPC_AIController.h"
#include "EPC_NPC.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"

UEPBTService_IsPlayerTooClose::UEPBTService_IsPlayerTooClose()
{
    bNotifyBecomeRelevant = true;
    NodeName = TEXT("Is Player Too Close");
}

void UEPBTService_IsPlayerTooClose::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AEPAIC_NPC_AIController const* const cont = Cast<AEPAIC_NPC_AIController>(OwnerComp.GetAIOwner());
    if (!cont) return;

    AEPC_NPC const* const npc = Cast<AEPC_NPC>(cont->GetPawn());
    if (!npc) return;

    ACharacter const* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (!player) return;

    float CurrentMinAttackRange = npc->GetMinAttackRange();

    bool bIsTooClose = npc->GetDistanceTo(player) < CurrentMinAttackRange;
    OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), bIsTooClose);
}
