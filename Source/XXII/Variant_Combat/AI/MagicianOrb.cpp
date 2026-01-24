#include "MagicianOrb.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

AMagicianOrb::AMagicianOrb()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetSphereRadius(CollisionRadius);
	CollisionComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	CollisionComponent->SetGenerateOverlapEvents(true);
	RootComponent = CollisionComponent;

	OrbMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OrbMesh"));
	OrbMesh->SetupAttachment(RootComponent);
	OrbMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (SphereMesh.Succeeded())
	{
		OrbMesh->SetStaticMesh(SphereMesh.Object);
		OrbMesh->SetWorldScale3D(FVector(0.5f));
	}
}

void AMagicianOrb::InitOrb(float InSpeed, float InDamage, float InLifespanSeconds, bool bInExplosive, float InExplosionRadius)
{
	Speed = InSpeed;
	Damage = InDamage;
	LifespanSeconds = InLifespanSeconds;
	bIsExplosive = bInExplosive;
	ExplosionRadius = InExplosionRadius;
}
