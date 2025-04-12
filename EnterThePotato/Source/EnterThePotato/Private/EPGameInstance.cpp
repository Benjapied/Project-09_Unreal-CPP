// Fill out your copyright notice in the Description page of Project Settings.


#include "EPGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UEPGameInstance::LoadMenuLevel(UWorld* InContext)
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(InContext, MenuLevel, true);
}

void UEPGameInstance::LoadGameLevel(UWorld* InContext)
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(InContext, GameLevel, true);
}
