#include "EPUW_WaveProgressBar.h"
#include "Components/ProgressBar.h"

void UEPUW_WaveProgressBar::NativeConstruct()
{
    Super::NativeConstruct();

    if (WaveProgressBar)
    {
        WaveProgressBar->SetPercent(0.0f);
    }
}

void UEPUW_WaveProgressBar::UpdateProgressBar(float Progress)
{
    if (WaveProgressBar)
    {
        WaveProgressBar->SetPercent(FMath::Clamp(Progress, 0.0f, 1.0f));
    }
}
