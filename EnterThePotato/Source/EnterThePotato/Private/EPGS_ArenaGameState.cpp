#include "EPGS_ArenaGameState.h"

void AEPGS_ArenaGameState::BeginPlay()
{
    Super::BeginPlay();

    if (WaveProgressBarClass)
    {
        WaveProgressBarWidget = CreateWidget<UEPUW_WaveProgressBar>(GetWorld(), WaveProgressBarClass);
        if (WaveProgressBarWidget)
        {
            WaveProgressBarWidget->AddToViewport();
        }
    }
}

void AEPGS_ArenaGameState::OnWaveStarted(int32 WaveIndex)
{
	UE_LOG(LogTemp, Log, TEXT("Wave %d started!"), WaveIndex);

    if (!WaveNotificationInstance && WaveNotificationClass)
    {
        WaveNotificationInstance = CreateWidget<UEPUW_WaveNotificationWidget>(GetWorld(), WaveNotificationClass);
        if (WaveNotificationInstance)
        {
            WaveNotificationInstance->AddToViewport();
        }
    }

    if (WaveNotificationInstance)
    {
        WaveNotificationInstance->SetWaveNumber(WaveIndex + 1);
        WaveNotificationInstance->PlayFadeAnimation();
    }
}

void AEPGS_ArenaGameState::OnWaveFinished(int32 WaveIndex)
{
	UE_LOG(LogTemp, Log, TEXT("Wave %d finished!"), WaveIndex);
    WaveProgressBarWidget->UpdateProgressBar(0);
}

void AEPGS_ArenaGameState::UpdateWaveProgress(int32 EnemiesRemaining, int32 TotalEnemies)
{
    if (WaveProgressBarWidget)
    {
        float Progress = 1.0f - (float(EnemiesRemaining) / float(TotalEnemies));
        WaveProgressBarWidget->UpdateProgressBar(Progress);
    }
}
