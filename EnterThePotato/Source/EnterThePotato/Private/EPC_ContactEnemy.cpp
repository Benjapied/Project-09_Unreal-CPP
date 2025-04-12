#include "EPC_ContactEnemy.h"

#include "Components/BoxComponent.h"
#include "Consts.h"

AEPC_ContactEnemy::AEPC_ContactEnemy() : RightFistCollisionBox{ CreateDefaultSubobject<UBoxComponent>(TEXT("RightFistCollisionBox")) }
{
	PrimaryActorTick.bCanEverTick = true;

	if (RightFistCollisionBox)
	{
		RightFistCollisionBox->SetBoxExtent(defs::RightFistBoxSize, false);
		FAttachmentTransformRules const Rules
		{
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::KeepWorld,
			false
		};

		//RightFistCollisionBox->AttachToComponent(GetMesh(), Rules, defs::RightFistSocketName);
		//RightFistCollisionBox->SetRelativeLocation(defs::CollisionBoxLocation);

	}

}

void AEPC_ContactEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEPC_ContactEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void AEPC_ContactEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (RightFistCollisionBox)
	{
		AEPC_CharacterBase* BaseCharacter = Cast<AEPC_CharacterBase>(this);
		if (BaseCharacter)
		{
			RightFistCollisionBox->OnComponentBeginOverlap.AddDynamic(BaseCharacter, &AEPC_CharacterBase::OnAttackOverlapBegin);
			RightFistCollisionBox->OnComponentEndOverlap.AddDynamic(BaseCharacter, &AEPC_CharacterBase::OnAttackOverlapEnd);
		}
	}
}

//void AEPC_ContactEnemy::AttackStart_Implementation()
//{
//	RightFistCollisionBox->SetCollisionProfileName("Damaging");
//	RightFistCollisionBox->SetNotifyRigidBodyCollision(true);
//}

//void AEPC_ContactEnemy::AttackEnd_Implementation()
//{
//	RightFistCollisionBox->SetCollisionProfileName("Damaging");
//	RightFistCollisionBox->SetNotifyRigidBodyCollision(false);
//}
