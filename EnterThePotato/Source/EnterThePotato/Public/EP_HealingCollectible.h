// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EP_BaseCollectible.h"
#include "EP_HealingCollectible.generated.h"

/**
 * 
 */
UCLASS()
class ENTERTHEPOTATO_API AEP_HealingCollectible : public AEP_BaseCollectible
{
	GENERATED_BODY()

public:

	virtual void OnCollect(AActor* actor) override;
	
};
