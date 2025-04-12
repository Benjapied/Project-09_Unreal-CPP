// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EPUI_WaveEventInterface.generated.h"

UINTERFACE(MinimalAPI)
class UEPUI_WaveEventInterface : public UInterface
{
	GENERATED_BODY()
};


class ENTERTHEPOTATO_API IEPUI_WaveEventInterface
{
	GENERATED_BODY()

public:
	virtual void OnWaveStarted(int32 WaveIndex) = 0;
	virtual void OnWaveFinished(int32 WaveIndex) = 0;
};
