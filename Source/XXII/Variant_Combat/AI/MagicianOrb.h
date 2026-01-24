#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MagicianOrb.generated.h"

class USphereComponent;

UCLASS()
class XXII_API AMagicianOrb : public AActor
{
	GENERATED_BODY()

public:
	AMagicianOrb();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* OrbMesh;

	UFUNCTION(BlueprintCallable, Category = "Orb")
	void InitOrb(float InSpeed, float InDamage, float InLifespanSeconds, bool bInExplosive, float InExplosionRadius);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orb")
	float Speed = 800.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orb")
	float Damage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orb")
	float LifespanSeconds = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orb")
	bool bIsExplosive = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orb")
	float ExplosionRadius = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orb")
	float CollisionRadius = 30.f;
};
