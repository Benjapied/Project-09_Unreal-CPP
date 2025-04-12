// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class ENTERTHEPOTATO_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
    public:
        virtual bool Initialize() override;

    protected:
        UPROPERTY(meta = (BindWidget))
        class UButton* PlayButton;

        UPROPERTY(meta = (BindWidget))
        class UButton* OptionsButton;

        UPROPERTY(meta = (BindWidget))
        class UButton* QuitButton;

        UFUNCTION()
        void OnPlayClicked();

        UFUNCTION()
        void OnOptionsClicked();

        UFUNCTION()
        void OnQuitClicked();
};
