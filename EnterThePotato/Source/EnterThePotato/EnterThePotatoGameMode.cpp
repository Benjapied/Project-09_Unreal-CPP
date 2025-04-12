// Copyright Epic Games, Inc. All Rights Reserved.

#include "EnterThePotatoGameMode.h"
#include "EnterThePotatoPlayerController.h"
#include "EnterThePotatoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEnterThePotatoGameMode::AEnterThePotatoGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AEnterThePotatoPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}

void AEnterThePotatoGameMode::BeginPlay()
{
	Super::BeginPlay();
}