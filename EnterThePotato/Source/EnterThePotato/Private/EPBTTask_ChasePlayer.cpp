// Fill out your copyright notice in the Description page of Project Settings.


#include "EPBTTask_ChasePlayer.h"

#include "EPAIC_NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

UEPBTTask_ChasePlayer::UEPBTTask_ChasePlayer(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UEPBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEPAIC_NPC_AIController* const cont = Cast<AEPAIC_NPC_AIController>(OwnerComp.GetAIOwner());
	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	bool const playerTooFar = OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());

	if (!cont || !player || !playerTooFar)
		return EBTNodeResult::Failed;

	FVector const PlayerLocation = player->GetActorLocation();

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(cont, PlayerLocation);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
