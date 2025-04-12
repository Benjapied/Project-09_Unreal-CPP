// Fill out your copyright notice in the Description page of Project Settings.

#include "EP_CrossbowProjectile.h"
#include "Components/SceneComponent.h"
#include "EPI_LifeInterface.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AEP_CrossbowProjectile::AEP_CrossbowProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_lifeTime = 3;
	m_currentLifeTime = 0;

	m_projectile = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile"));
	RootComponent = m_projectile;

	m_projectileStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Static Mesh"));
	m_projectileStaticMesh->SetupAttachment(GetRootComponent());
	
	m_projectileStaticMesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	m_projectileStaticMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	m_projectileStaticMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	

	InitProjectileComponent();

}

// Called when the game starts or when spawned
void AEP_CrossbowProjectile::BeginPlay()
{
	Super::BeginPlay();

	
	
}

// Called every frame
void AEP_CrossbowProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_currentLifeTime += DeltaTime;
	if (m_currentLifeTime >= m_lifeTime) {
		Destroy();
	}

}

void AEP_CrossbowProjectile::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) {

	if (OtherActor == this || OtherActor == m_owner || m_owner == nullptr) {
		return;
	}

	IEPI_LifeInterface* obj = Cast<IEPI_LifeInterface>(OtherActor);

	if (obj) {

		UE_LOG(LogTemp, Warning, TEXT("JE MET DES DGT AVEC LE PROJECTILE ICI "));

		obj->TakeDamage(m_damage);
		Destroy();

	}

}

void AEP_CrossbowProjectile::InitProjectileComponent() {

	m_projectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	m_projectileComponent->InitialSpeed = 1500;
	m_projectileComponent->MaxSpeed = 1500;
	m_projectileComponent->bRotationFollowsVelocity = true;
	m_projectileComponent->bShouldBounce = true;
	m_projectileComponent->ProjectileGravityScale = 0;
}

void AEP_CrossbowProjectile::InitProjectile(AActor* actor, float damage) {

	m_damage = damage;
	m_owner = actor;

	m_projectileStaticMesh->OnComponentBeginOverlap.AddDynamic(this, &AEP_CrossbowProjectile::OnBoxBeginOverlap);

}