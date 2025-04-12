// Fill out your copyright notice in the Description page of Project Settings.


#include "EP_Sword.h"
#include "EPI_LifeInterface.h"

#include "Components/StaticMeshComponent.h"

AEP_Sword::AEP_Sword() {


	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	m_swordMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	m_swordMeshComponent->SetupAttachment(RootComponent);
	m_swordMeshComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	m_cube = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBoxCollision"));
	m_cube->SetupAttachment(GetRootComponent());
	m_cube->SetCollisionProfileName(TEXT("NoCollision"));

	m_damage = 500;
}

void AEP_Sword::BeginPlay() {

	Super::BeginPlay();

	m_cube->OnComponentBeginOverlap.AddDynamic(this, &AEP_Sword::SwordOverlap);
}

void AEP_Sword::OnActivateWeapon(AActor* aactor) 
{

	if (!m_canAttack) {
		return;
	}

	FTransform NewTransform;
	NewTransform.SetLocation(aactor->GetActorLocation() + aactor->GetActorForwardVector()); 
	NewTransform.SetRotation(FQuat::MakeFromEuler(FVector(0))); 

	m_cube->SetWorldTransform(NewTransform);

	m_cube->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	m_cube->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

void AEP_Sword::OnDesactivateWeapon() 
{
	m_cube->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_cube->SetCollisionProfileName(TEXT("NoCollision"));
}

void AEP_Sword::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
}

void AEP_Sword::SwordOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	IEPI_LifeInterface* obj = Cast<IEPI_LifeInterface>(OtherActor);

	if (OtherActor == m_owner)
	{
		return;
	}

	if (obj) {
		obj->TakeDamage(m_damage);
	}
}

