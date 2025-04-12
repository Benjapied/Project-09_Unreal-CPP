#include "EPBTTask_StandStill.h"
#include "EPAIC_NPC_AIController.h"
#include "EPC_NPC.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

UEPBTTask_StandStill::UEPBTTask_StandStill(FObjectInitializer const& ObjectInitializer)
{
    NodeName = TEXT("Stand Still");
}

EBTNodeResult::Type UEPBTTask_StandStill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AEPAIC_NPC_AIController* const cont = Cast<AEPAIC_NPC_AIController>(OwnerComp.GetAIOwner());
    bool const playerInRange = OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
    AEPC_NPC* const npc = Cast<AEPC_NPC>(cont->GetPawn());

    if (!cont || !playerInRange || !npc)
        return EBTNodeResult::Failed;

    npc->GetCharacterMovement()->StopMovementImmediately();

    ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (player)
    {
        FVector DirectionToPlayer = player->GetActorLocation() - npc->GetActorLocation();
        DirectionToPlayer.Z = 0.f;

        FRotator LookAtRotation = DirectionToPlayer.Rotation();

        npc->SetActorRotation(LookAtRotation);
    }

    return EBTNodeResult::Succeeded;
}
