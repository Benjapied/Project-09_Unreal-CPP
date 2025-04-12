// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EPI_CanHasWeapon.h"
#include "EP_BaseWeapon.generated.h"

UCLASS()
class ENTERTHEPOTATO_API AEP_BaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	

	AEP_BaseWeapon();

protected:

	virtual void BeginPlay() override;

	int m_damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_cooldown;
	bool m_canAttack = true;
	float m_progressCooldown = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* m_owner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString m_socket;

public:	

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnActivateWeapon(AActor* aactor);
	
	UFUNCTION()
	virtual void OnDesactivateWeapon();

	
	virtual void SetOwner(AActor* actor);

	virtual void SetDamage(float dmg);
	virtual float GetDamage();

	virtual FString GetSocketName();

};
