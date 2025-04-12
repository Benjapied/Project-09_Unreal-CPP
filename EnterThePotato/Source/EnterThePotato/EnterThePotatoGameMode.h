// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnterThePotatoGameMode.generated.h"

UCLASS(minimalapi)
class AEnterThePotatoGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AEnterThePotatoGameMode();
	virtual void BeginPlay() override;
};



