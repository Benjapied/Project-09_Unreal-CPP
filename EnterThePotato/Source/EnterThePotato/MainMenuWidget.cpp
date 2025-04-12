// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "EPGameInstance.h"

bool UMainMenuWidget::Initialize()
{
    bool Success = Super::Initialize();
    if (!Success) return false;

    // Trouver les boutons par leur nom

    if (PlayButton)
        PlayButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnPlayClicked);

    if (OptionsButton)
        OptionsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnOptionsClicked);

    if (QuitButton)
        QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitClicked);

    return true;
}

void UMainMenuWidget::OnPlayClicked()
{
    UEPGameInstance* gameInstance = Cast<UEPGameInstance>(GetGameInstance());
    UE_LOG(LogTemp, Warning, TEXT("Bouton Jouer cliqué !"));
    UWorld* World = GetWorld();
    if (World && gameInstance)
    {
        gameInstance->LoadGameLevel(World);
    }
}

void UMainMenuWidget::OnOptionsClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("Bouton Options cliqué !"));
}

void UMainMenuWidget::OnQuitClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("Bouton Quitter cliqué !"));
    UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, true);
}
