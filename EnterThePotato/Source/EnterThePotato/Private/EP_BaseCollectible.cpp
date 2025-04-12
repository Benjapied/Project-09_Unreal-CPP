// Fill out your copyright notice in the Description page of Project Settings.


#include "EP_BaseCollectible.h"

// Sets default values
AEP_BaseCollectible::AEP_BaseCollectible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Collectible"));
	m_meshComponent->SetupAttachment(GetRootComponent());
	m_meshComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	m_meshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	m_meshComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

}

// Called when the game starts or when spawned
void AEP_BaseCollectible::BeginPlay()
{
	Super::BeginPlay();

	m_meshComponent->OnComponentBeginOverlap.AddDynamic(this, &AEP_BaseCollectible::OnBoxOverlap);
	
	m_startingZ = GetActorLocation().Z;
	m_endZ = m_startingZ + 20;
	m_bobingProgress = 0;

}

// Called every frame
void AEP_BaseCollectible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorRotation(GetActorRotation().Add(0.0f, DeltaTime * 35, 0.0f));

	m_bobingProgress += DeltaTime * 2;
	float Zpos = FMath::Sin(m_bobingProgress) ;
	FVector newPos = FVector(GetActorLocation().X, GetActorLocation().Y, FMath::Lerp(m_startingZ, m_endZ, Zpos));

	SetActorLocation(newPos);

}

void AEP_BaseCollectible::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnCollect(OtherActor);
}

void AEP_BaseCollectible::OnCollect(AActor* actor)
{
	//On collecte ici
}

