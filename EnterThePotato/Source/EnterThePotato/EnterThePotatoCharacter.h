// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "../EnterThePotato/Public/EPC_CharacterBase.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/Character.h"

#include "EPI_CanHasWeapon.h"
#include "Components/SphereComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"

#include "EnterThePotatoCharacter.generated.h"


UCLASS(Blueprintable)
class AEnterThePotatoCharacter : public AEPC_CharacterBase
{
	GENERATED_BODY()

public:
	AEnterThePotatoCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Fonction pour zoomer avec la molette */
	void zoomCameraCharacter();
	void unZoomCameraCharacter();

	void PickUpAction();
	void HitAction();
	void ThrowAction();

protected:
	/** Facteur de vitesse du zoom */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float ZoomSpeed = 100.0f;

	/** Distance minimale du zoom */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MinZoom = 300.0f;

	/** Distance maximale du zoom */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MaxZoom = 1200.0f;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
};

