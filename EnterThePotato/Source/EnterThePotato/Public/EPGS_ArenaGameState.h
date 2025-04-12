#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "EPUI_WaveEventInterface.h"
#include "EPUW_WaveProgressBar.h"
#include "EPUW_WaveNotificationWidget.h"
#include "EPGS_ArenaGameState.generated.h"

UCLASS()
class ENTERTHEPOTATO_API AEPGS_ArenaGameState : public AGameStateBase, public IEPUI_WaveEventInterface
{
	GENERATED_BODY()

public:

	virtual void OnWaveStarted(int32 WaveIndex) override;
	virtual void OnWaveFinished(int32 WaveIndex) override;

    void UpdateWaveProgress(int32 EnemiesRemaining, int32 TotalEnemies);

protected:

    virtual void BeginPlay() override;

private:

    UPROPERTY()
    class UEPUW_WaveProgressBar* WaveProgressBarWidget;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class UEPUW_WaveProgressBar> WaveProgressBarClass;

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UEPUW_WaveNotificationWidget> WaveNotificationClass;

    UPROPERTY()
    UEPUW_WaveNotificationWidget* WaveNotificationInstance;
};
