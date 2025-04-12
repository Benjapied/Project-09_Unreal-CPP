// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EPUW_WaveProgressBar.generated.h"


UCLASS()
class ENTERTHEPOTATO_API UEPUW_WaveProgressBar : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "WaveProgress")
    void UpdateProgressBar(float Progress);

protected:
    virtual void NativeConstruct() override;

private:
    UPROPERTY(meta = (BindWidget))
    class UProgressBar* WaveProgressBar;
	
};
