#pragma once

#include "CoreMinimal.h"
#include "MagicianAttackTypes.generated.h"

USTRUCT(BlueprintType)
struct FMagicianPhaseSegment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orb")
	int32 OrbAmount = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orb")
	float OrbSpawnRate = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orb")
	float OrbSpeed = 800.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orb")
	float OrbDamage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orb")
	float OrbLifespanSeconds = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orb")
	bool bIsExplosive = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orb", meta = (EditCondition = "bIsExplosive"))
	float ExplosiveOrbDamageRadius = 200.f;
};

USTRUCT(BlueprintType)
struct FMagicianPhase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Phase")
	float MovementSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Phase")
	TArray<FMagicianPhaseSegment> Segments;
};
