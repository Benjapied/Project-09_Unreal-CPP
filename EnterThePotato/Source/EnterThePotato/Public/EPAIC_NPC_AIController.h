// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EPAIC_NPC_AIController.generated.h"

/**
 * 
 */
UCLASS()
class ENTERTHEPOTATO_API AEPAIC_NPC_AIController : public AAIController
{
	GENERATED_BODY()
	
public:

	explicit AEPAIC_NPC_AIController(FObjectInitializer const& ObjectInitializer);

protected:

	virtual void OnPossess(APawn* InPawn) override;
};
