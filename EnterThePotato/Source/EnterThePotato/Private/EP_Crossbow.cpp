// Fill out your copyright notice in the Description page of Project Settings.


#include "EP_Crossbow.h"
#include "EP_CrossbowProjectile.h"

// Sets default values
AEP_Crossbow::AEP_Crossbow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	m_crossbowHandler = CreateDefaultSubobject<USceneComponent>(TEXT("Crossbow Handler"));
	m_crossbowHandler->SetupAttachment(RootComponent);

	m_socket = "crossbow_rHand";
}

// Called when the game starts or when spawned
void AEP_Crossbow::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEP_Crossbow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEP_Crossbow::OnActivateWeapon(AActor* aactor) {

	Super::OnActivateWeapon(aactor);

	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AEP_CrossbowProjectile* projectile = GetWorld()->SpawnActor<AEP_CrossbowProjectile>(
		m_projectileActor, 
		aactor->GetActorLocation() + (aactor->GetActorForwardVector() * 50), 
		aactor->GetActorRotation(), 
		SpawnParams);

	projectile->SetActorEnableCollision(false);
	projectile->InitProjectile(aactor, m_damage);
	projectile->SetActorEnableCollision(true);
	

	m_canAttack = false;

}
