// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "EPGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ENTERTHEPOTATO_API UEPGameInstance : public UGameInstance
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> MenuLevel;
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> GameLevel;
public:
	UFUNCTION(BlueprintCallable)
	void LoadMenuLevel(UWorld* InContext);
	UFUNCTION(BlueprintCallable)
	void LoadGameLevel(UWorld* InContext);
};
