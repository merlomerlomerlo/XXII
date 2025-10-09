// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = ProjectileMesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	if (MeshObj.Succeeded())
	{
		ProjectileMesh->SetStaticMesh(MeshObj.Object);
		ProjectileMesh->SetWorldScale3D(FVector(0.1f, 0.1f, 0.5f));
	}

	ProjectileTimer = CreateDefaultSubobject<UTimerComponent>(FName("ProjectileTimer"));
	ProjectileTimer->RegisterComponent();

	ProjectileTimer->TimerDuration = ProjectileLife;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileTimer->StartTimer();
	ProjectileTimer->OnTimerFinished.AddLambda([this]()
	{
		Destroy();
	});
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(GetActorLocation() + Direction * Speed * DeltaTime);
}

void AProjectile::InitProjectile(const FVector& SpawnLocation, const FVector& ForwardVector)
{
	SetActorLocation(SpawnLocation);
	SetActorRotation(ForwardVector.Rotation() + FRotator(90.f, 0.f, 0.f));
	Direction = ForwardVector.GetSafeNormal();
}