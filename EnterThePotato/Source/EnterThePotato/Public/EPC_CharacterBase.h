#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EPUI_Combat.h"
#include "EPI_CanHasWeapon.h"
#include "Components/SphereComponent.h"
#include "EPI_LifeInterface.h"
#include "EPDA_AttackData.h"
#include "EPC_CharacterBase.generated.h"

UCLASS()
class ENTERTHEPOTATO_API AEPC_CharacterBase : public ACharacter, 
	public IEPUI_Combat, 
	public IEPI_CanHasWeapon,
	public IEPI_LifeInterface
{
	GENERATED_BODY()

public:

	AEPC_CharacterBase();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region Health Methods

	float GetHealth() override;
	float GetMaxHealth() override;
	void SetHealth(float NewHealth) override;
	void TakeDamage(float damage) override;

#pragma endregion

#pragma region EPI_CanHaveWeapon

	void ThrowWeapon_Implementation() override;
	AEP_BaseWeapon* GetCurrentWeapon_Implementation() override;
	void SetCurrentWeapon_Implementation(AEP_BaseWeapon* weapon) override;

	UPROPERTY()
	AEP_BaseWeapon* m_weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USphereComponent* m_spherePickup;

	UPROPERTY()
	float m_pickUpRange = 10;

#pragma endregion

#pragma region CombatInterface

	int Attack_Implementation(UEP_AttackType type) override;

	void AttackStart_Implementation() override;

	void AttackEnd_Implementation() override;

	UAnimMontage* GetMontage() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	TArray<UEPDA_AttackData*> m_attackList;

	float m_cdProgress = 0;
	float m_currentCd = 0;

#pragma endregion

protected:

	virtual void BeginPlay() override;

public:

#pragma region Attack Methods

	UFUNCTION()
	void OnAttackOverlapBegin
	(
		UPrimitiveComponent* const OverlappedComponent,
		AActor* const OtherActor,
		UPrimitiveComponent* const OtherComponent,
		int const OtherBodyIndex,
		bool const FromSweep,
		FHitResult const& SweepResult
	);

	UFUNCTION()
	void OnAttackOverlapEnd
	(
		UPrimitiveComponent* const OverlappedComponent,
		AActor* const OtherActor,
		UPrimitiveComponent* const OtherComponent,
		int const OtherBodyIndex
	);

#pragma endregion

private:

#pragma region Health Fields

	float const MaxHealth{ 100.f };
	float Health;

#pragma endregion

#pragma region Damage Fields

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	float Damage;

#pragma endregion

};
