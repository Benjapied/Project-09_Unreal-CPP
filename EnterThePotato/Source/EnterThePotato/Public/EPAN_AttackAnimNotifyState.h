// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "EPAN_AttackAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class ENTERTHEPOTATO_API UEPAN_AttackAnimNotifyState : public UAnimNotifyState
{

public:

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:

	GENERATED_BODY()
	
};
