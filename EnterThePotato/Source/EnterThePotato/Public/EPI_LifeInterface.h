// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EPI_LifeInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEPI_LifeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ENTERTHEPOTATO_API IEPI_LifeInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual float GetHealth() = 0;
	virtual float GetMaxHealth() = 0;
	virtual void SetHealth(float NewHealth) = 0;
	virtual void TakeDamage(float damage) = 0;

};
