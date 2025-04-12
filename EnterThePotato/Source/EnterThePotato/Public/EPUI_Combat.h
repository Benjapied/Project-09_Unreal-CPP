// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EP_AttackType.h"
#include "EPUI_Combat.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEPUI_Combat : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ENTERTHEPOTATO_API IEPUI_Combat
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	int Attack(UEP_AttackType type);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void AttackStart();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void AttackEnd();
	
};
