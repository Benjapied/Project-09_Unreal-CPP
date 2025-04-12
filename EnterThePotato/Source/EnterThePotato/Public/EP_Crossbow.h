// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "./../EP_BaseWeapon.h"
#include "Components/SceneComponent.h"
#include "EP_Crossbow.generated.h"

UCLASS()
class ENTERTHEPOTATO_API AEP_Crossbow: public AEP_BaseWeapon
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEP_Crossbow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnActivateWeapon(AActor* aactor) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* m_crossbowHandler;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AEP_CrossbowProjectile> m_projectileActor;

};
