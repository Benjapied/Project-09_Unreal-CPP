// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "EP_AttackType.generated.h"

/**
 * 
 */
UENUM()
enum class UEP_AttackType : uint8
{
	BaseAttack = 0,
	HeavyAttack = 1
};
