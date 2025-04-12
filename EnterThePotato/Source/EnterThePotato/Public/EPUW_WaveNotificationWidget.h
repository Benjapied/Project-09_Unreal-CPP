#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EPUW_WaveNotificationWidget.generated.h"

UCLASS()
class ENTERTHEPOTATO_API UEPUW_WaveNotificationWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, Category = "Wave Notification")
    void SetWaveNumber(int32 WaveNumber);

    UFUNCTION(BlueprintCallable, Category = "Wave Notification")
    void PlayFadeAnimation();

protected:

    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* FadeInOut;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* WaveText;
};
