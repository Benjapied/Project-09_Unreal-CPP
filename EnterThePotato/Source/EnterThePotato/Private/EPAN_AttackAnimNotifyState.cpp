// Fill out your copyright notice in the Description page of Project Settings.


#include "EPAN_AttackAnimNotifyState.h"
#include "EPC_CharacterBase.h"
#include "EPUI_Combat.h"

void UEPAN_AttackAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (IEPUI_Combat* const icombat = Cast<IEPUI_Combat>(MeshComp->GetOwner()))
		{
			
			icombat->Execute_AttackStart(MeshComp->GetOwner());
		}
	}
}

void UEPAN_AttackAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (IEPUI_Combat* const icombat = Cast<IEPUI_Combat>(MeshComp->GetOwner()))
		{
			icombat->Execute_AttackEnd(MeshComp->GetOwner());
		}
	}
}
