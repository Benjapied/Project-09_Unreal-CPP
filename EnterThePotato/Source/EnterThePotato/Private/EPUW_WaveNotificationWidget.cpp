#include "EPUW_WaveNotificationWidget.h"
#include "Components/TextBlock.h"

void UEPUW_WaveNotificationWidget::SetWaveNumber(int32 WaveNumber)
{
    if (WaveText)
    {
        FText WaveFormattedText = FText::Format(NSLOCTEXT("Wave", "WaveNumber", "Wave {0}"), FText::AsNumber(WaveNumber));
        WaveText->SetText(WaveFormattedText);

        FString WaveString = WaveFormattedText.ToString();
        UE_LOG(LogTemp, Log, TEXT("WaveText set to: %s"), *WaveString);
    }
}


void UEPUW_WaveNotificationWidget::PlayFadeAnimation()
{
    if (FadeInOut)
    {
        PlayAnimation(FadeInOut);
    }
}
