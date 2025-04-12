#include "MainMenuGameMod.h"
#include "EnterThePotatoPlayerController.h"

void AMainMenuGameMod::BeginPlay()
{
    Super::BeginPlay();

    if (MainMenuWidgetClass)
    {
        MainMenuWidget = CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass);

        if (MainMenuWidget)
        {
            MainMenuWidget->AddToViewport();

            APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
            if (PlayerController)
            {
                PlayerController->bShowMouseCursor = true;
                PlayerController->SetInputMode(FInputModeUIOnly());
            }
        }
    }
}
