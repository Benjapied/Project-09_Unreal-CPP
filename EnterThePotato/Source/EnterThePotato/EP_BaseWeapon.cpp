// Fill out your copyright notice in the Description page of Project Settings.


#include "EP_BaseWeapon.h"

// Sets default values
AEP_BaseWeapon::AEP_BaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	m_socket = "sword_rHand";
}

void AEP_BaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEP_BaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!m_canAttack) {
		m_progressCooldown += DeltaTime;
		if (m_progressCooldown >= m_cooldown) {
			m_progressCooldown = 0;
			m_canAttack = true;
		}
	}

}

void AEP_BaseWeapon::OnActivateWeapon(AActor* aactor) {

}

void AEP_BaseWeapon::OnDesactivateWeapon() {

}

void AEP_BaseWeapon::SetOwner(AActor* actor) {

	m_owner = actor;

}

void AEP_BaseWeapon::SetDamage(float dmg)
{
	m_damage = dmg;
}

float AEP_BaseWeapon::GetDamage()
{
	return m_damage;
}

FString AEP_BaseWeapon::GetSocketName() {

	return m_socket;

}