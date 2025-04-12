// Fill out your copyright notice in the Description page of Project Settings.


#include "EPC_CharacterBase.h"
#include "EnterThePotato/EnterThePotatoCharacter.h"
#include "../EP_BaseWeapon.h"
#include "EPC_NPC.h"

AEPC_CharacterBase::AEPC_CharacterBase() : 
	Health{MaxHealth}
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEPC_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AEPC_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_cdProgress += DeltaTime;

}

void AEPC_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

#pragma region LifeInterface

float AEPC_CharacterBase::GetHealth()
{
	return Health;
}

float AEPC_CharacterBase::GetMaxHealth()
{
	return MaxHealth;
}

void AEPC_CharacterBase::SetHealth(float NewHealth)
{
	Health = NewHealth;

	if (Cast<AEnterThePotatoCharacter>(this))
	{
		if (Health <= 0)
		{
			UE_LOG(LogTemp, Error, TEXT("YOU LOSE !!!"));
			GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
		}
	}
	else if (AEPC_NPC* npc = Cast<AEPC_NPC>(this))
	{
		if (Health <= 0)
		{
			UE_LOG(LogTemp, Error, TEXT("You Killed !!!"));
			npc->Destroy();
		}
	}
}

void AEPC_CharacterBase::TakeDamage(float damage) {

	SetHealth(GetHealth() - damage);
}

#pragma endregion

void AEPC_CharacterBase::OnAttackOverlapBegin
(
	UPrimitiveComponent* const OverlappedComponent,
	AActor* const OtherActor,
	UPrimitiveComponent* const OtherComponent,
	int const OtherBodyIndex, bool const FromSweep,
	FHitResult const& SweepResult
)
{
	
	if (OtherActor == this) return;

	if (AEPC_CharacterBase* const Opponent = Cast<AEPC_CharacterBase>(OtherActor))
	{
		float NewHealth = Opponent->GetHealth() - Damage;
		Opponent->SetHealth(NewHealth);
	}
}

void AEPC_CharacterBase::OnAttackOverlapEnd
(
	UPrimitiveComponent* const OverlappedComponent,
	AActor* const OtherActor,
	UPrimitiveComponent* const OtherComponent,
	int const OtherBodyIndex
)
{
}

#pragma region CanHaveWeaponInterface

void AEPC_CharacterBase::ThrowWeapon_Implementation() {

	if (m_weapon == nullptr) {
		return;
	}

	m_weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	m_weapon->SetActorEnableCollision(true);

	m_weapon = nullptr;

};

AEP_BaseWeapon* AEPC_CharacterBase::GetCurrentWeapon_Implementation() {
	return m_weapon;
};

void AEPC_CharacterBase::SetCurrentWeapon_Implementation(AEP_BaseWeapon* weapon) {

	m_weapon = weapon;

	FName SocketName = FName(*m_weapon->GetSocketName());
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);

	m_weapon->AttachToComponent(GetMesh(), AttachmentRules, SocketName);
	m_weapon->SetOwner(this);

};

#pragma endregion

#pragma region CombatInterface

int AEPC_CharacterBase::Attack_Implementation(UEP_AttackType type) {

	UAnimMontage* anim = nullptr;
	
	if (m_cdProgress < m_currentCd) {
		return 0;
	}

	//Securité pour play une anim si ya rien dans la liste des attaques
	if (m_attackList.Num() == 0) {
		if (Montage)
		{
			PlayAnimMontage(Montage);
		}
		return 0;
	}

	for (int i = 0; i < m_attackList.Num(); i++) {

		if (m_attackList[i]->m_type == type) {

			if (m_attackList[i]->m_weaponType == m_weapon->GetClass()) {

				anim = m_attackList[i]->m_animMontage;
				m_weapon->SetDamage(m_attackList[i]->m_damage);
				m_currentCd = m_attackList[i]->m_cooldown;
				break;
			}
		}
	}

	if (anim)
	{
		PlayAnimMontage(anim);
		m_cdProgress = 0;
	}
	return 0;

}

void AEPC_CharacterBase::AttackStart_Implementation() {

	if (m_weapon == nullptr) {
		return;
	}


	m_weapon->OnActivateWeapon(this);

}

void AEPC_CharacterBase::AttackEnd_Implementation() {

	if (m_weapon == nullptr) {
		return;
	}

	m_weapon->OnDesactivateWeapon();

}

UAnimMontage* AEPC_CharacterBase::GetMontage() const
{
	return Montage;
}

#pragma endregion