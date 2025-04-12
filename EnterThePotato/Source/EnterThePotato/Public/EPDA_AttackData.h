// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "EP_AttackType.h"
#include "../EP_BaseWeapon.h"

#include "EPDA_AttackData.generated.h"



/**
 * 
 */
UCLASS(BlueprintType)
class ENTERTHEPOTATO_API UEPDA_AttackData : public UDataAsset
{
public:

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AEP_BaseWeapon> m_weaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UEP_AttackType m_type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* m_animMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_cooldown;
	
};
