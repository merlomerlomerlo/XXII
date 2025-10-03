// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimerComponent.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class XXII_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ProjectileMesh;

	// Movement speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Projectile")
	float Speed = 2000.f;

	// Lifetime before auto-destroy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Projectile")
	float ProjectileLife = 1.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	UTimerComponent* ProjectileTimer;

	UPROPERTY()
	FVector Direction;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void InitProjectile(const FVector& SpawnLocation, const FVector& ForwardVector);
};
