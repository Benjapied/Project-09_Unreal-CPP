// Fill out your copyright notice in the Description page of Project Settings.


#include "EP_Poutch.h"

// Sets default values
AEP_Poutch::AEP_Poutch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	m_cube = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));

	m_cube->SetRelativeTransform(
		FTransform(
			(
				FQuat::MakeFromEuler({ 0,0,0 }),
				FVector(0, 0, 0),
				FVector(1)
				)
		)
	);

	m_cube->SetupAttachment(GetRootComponent());
	m_cube->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	m_cube->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

}

// Called when the game starts or when spawned
void AEP_Poutch::BeginPlay()
{
	Super::BeginPlay();
	
	m_cube->OnComponentBeginOverlap.AddDynamic(this, &AEP_Poutch::SwordOverlap);

}

// Called every frame
void AEP_Poutch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AEP_Poutch::GetHealth()
{
	return Health;
}

float AEP_Poutch::GetMaxHealth()
{
	return MaxHealth;
}

void AEP_Poutch::SetHealth(float NewHealth)
{
	
}

void AEP_Poutch::TakeDamage(float damage) {

	SetHealth(GetHealth() - damage);
}

void AEP_Poutch::SwordOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
}