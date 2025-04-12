// Copyright Epic Games, Inc. All Rights Reserved.

#include "EnterThePotatoCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

#include "EP_BaseWeapon.h"

AEnterThePotatoCharacter::AEnterThePotatoCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	//Sphere de pickup d'object
	m_spherePickup = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	m_spherePickup->SetRelativeTransform(
		FTransform(
			(
				FQuat::MakeFromEuler({ 0,0,0 }),
				FVector(0, 0, 0),
				FVector(1)
			)
		)
	);
	m_spherePickup->SetupAttachment(GetRootComponent());

	m_spherePickup->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	m_spherePickup->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	m_spherePickup->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

}

void AEnterThePotatoCharacter::BeginPlay() {

	Super::BeginPlay();
}

void AEnterThePotatoCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

}

void AEnterThePotatoCharacter::zoomCameraCharacter()
{
	if (CameraBoom)
	{
		// Calculer la nouvelle distance de la caméra
		float NewArmLength = CameraBoom->TargetArmLength - (1.f * ZoomSpeed);

		// Limiter le zoom dans les valeurs min et max
		CameraBoom->TargetArmLength = FMath::Clamp(NewArmLength, MinZoom, MaxZoom);
	}
}

void AEnterThePotatoCharacter::unZoomCameraCharacter()
{
	if (CameraBoom)
	{
		// Calculer la nouvelle distance de la caméra
		float NewArmLength = CameraBoom->TargetArmLength + (1.f * ZoomSpeed);

		// Limiter le zoom dans les valeurs min et max
		CameraBoom->TargetArmLength = FMath::Clamp(NewArmLength, MinZoom, MaxZoom);
	}
}

#pragma region Weapon Pickup Methods

void AEnterThePotatoCharacter::PickUpAction() {
		
	TArray<AActor*> OverlappingActors;
	m_spherePickup->GetOverlappingActors(OverlappingActors, AEP_BaseWeapon::StaticClass());

	if (OverlappingActors.Num() != 0) {

		AEP_BaseWeapon* weapon = Cast<AEP_BaseWeapon>(OverlappingActors[0]);
		Execute_SetCurrentWeapon(this, weapon);
	}

}

void AEnterThePotatoCharacter::HitAction() {

	if (m_weapon == nullptr) {
		return;
	}

	//Trigger l'animation d'attaque ici, on hit 
	Execute_Attack(this, UEP_AttackType::BaseAttack);

	
}

void AEnterThePotatoCharacter::ThrowAction() {

	Execute_ThrowWeapon(this);

}

#pragma endregion
