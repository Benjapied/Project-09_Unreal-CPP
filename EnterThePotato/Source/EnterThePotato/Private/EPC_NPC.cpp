#include "EPC_NPC.h"

AEPC_NPC::AEPC_NPC()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEPC_NPC::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (!m_weaponType) {
		return;
	}

	Execute_SetCurrentWeapon(this, GetWorld()->SpawnActor<AEP_BaseWeapon>(m_weaponType, GetActorLocation(), GetActorRotation(), SpawnParams));

}

void AEPC_NPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEPC_NPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UBehaviorTree* AEPC_NPC::GetBehaviorTree() const
{
	return Tree;
}

float AEPC_NPC::GetMinAttackRange() const
{
	return MinAttackRange;
}

float AEPC_NPC::GetMaxAttackRange() const
{
	return MaxAttackRange;
}

//int AEPC_NPC::Attack_Implementation(UEP_AttackType type)
//{
//	if (m_attackList.Num() != 0) {
//		Super::Attack_Implementation(type);
//		return 0;
//	}
//
//	if (Montage)
//	{
//		PlayAnimMontage(Montage);
//	}
//	return 0;
//}
