// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "EnterThePotatoPlayerController.generated.h"


/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class AEnterThePotatoPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AEnterThePotatoPlayerController();

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationClickAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationTouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SetDestinationKeyboardAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SetDestinationSprint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SetDestinationZoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SetDestinationUnZoom;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SetDestinationPause;

#pragma region Weapon

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PickUpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* HitAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ThrowAction;

#pragma endregion

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> PauseMenuClass;

	UFUNCTION()
	void onMove(const FInputActionValue& Value);

	UFUNCTION()
	void onSprint();
	UFUNCTION()
	void notOnSprint();
	UFUNCTION()
	void zoomCamera();
	UFUNCTION()
	void unZoomCamera();
	UFUNCTION()
	void pauseGame();
	UFUNCTION()
	// To add mapping context
	virtual void BeginPlay();

	/** Input handlers for SetDestination action. */
	UFUNCTION()
	void OnInputStarted();
	UFUNCTION()
	void OnSetDestinationTriggered();
	UFUNCTION()
	void OnSetDestinationReleased();
	UFUNCTION()
	void OnTouchTriggered();
	UFUNCTION()
	void OnTouchReleased();

	void RotatePlayerToMouse();

	//WEAPON 
	void PickUpActionHandler(const FInputActionValue& Value);
	void HitActionHandler(const FInputActionValue& Value);
	void ThrowActionHandler(const FInputActionValue& Value);

private:
	FVector CachedDestination;
	UUserWidget* PauseMenuInstance;

	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed
	float startSpeed;
	float sprintSpeed;
	float speed;
	bool isPaused;
};


