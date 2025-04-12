#include "EPBTTask_MoveAwayFromPlayer.h"

#include "EPAIC_NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

UEPBTTask_MoveAwayFromPlayer::UEPBTTask_MoveAwayFromPlayer(FObjectInitializer const& ObjectInitializer)
{
    NodeName = TEXT("Move Away From Player");
}

EBTNodeResult::Type UEPBTTask_MoveAwayFromPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEPAIC_NPC_AIController* const cont = Cast<AEPAIC_NPC_AIController>(OwnerComp.GetAIOwner());
	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	bool const playerTooClose = OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());

	if (!cont || !player || !playerTooClose)
		return EBTNodeResult::Failed;

	FVector const PlayerLocation = player->GetActorLocation();
	FVector const NPCLocation = cont->GetPawn()->GetActorLocation();

	FVector DirectionAway = (NPCLocation - PlayerLocation).GetSafeNormal();

	FVector TargetLocation = NPCLocation + DirectionAway * 50;

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(cont, TargetLocation);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
