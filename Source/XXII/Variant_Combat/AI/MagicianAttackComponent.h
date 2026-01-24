#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MagicianAttackTypes.h"
#include "MagicianAttackComponent.generated.h"

class AMagicianOrb;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPhaseCompleted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllPhasesCompleted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSegmentCompleted, int32, SegmentIndex);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class XXII_API UMagicianAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMagicianAttackComponent();

	// Configuration
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magician|Attack")
	TArray<FMagicianPhase> Phases;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magician|Attack")
	TSubclassOf<AMagicianOrb> OrbClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magician|Attack")
	TSubclassOf<AMagicianOrb> ExplosiveOrbClass;

	// Delegates
	UPROPERTY(BlueprintAssignable, Category = "Magician|Attack")
	FOnPhaseCompleted OnPhaseCompleted;

	UPROPERTY(BlueprintAssignable, Category = "Magician|Attack")
	FOnAllPhasesCompleted OnAllPhasesCompleted;

	UPROPERTY(BlueprintAssignable, Category = "Magician|Attack")
	FOnSegmentCompleted OnSegmentCompleted;

	// Control
	UFUNCTION(BlueprintCallable, Category = "Magician|Attack")
	void StartAttackSequence();

	UFUNCTION(BlueprintCallable, Category = "Magician|Attack")
	void StopAttackSequence();

	UFUNCTION(BlueprintCallable, Category = "Magician|Attack")
	void StartPhase(int32 PhaseIndex);

	UFUNCTION(BlueprintPure, Category = "Magician|Attack")
	bool IsAttacking() const { return bIsAttacking; }

	UFUNCTION(BlueprintPure, Category = "Magician|Attack")
	int32 GetCurrentPhaseIndex() const { return CurrentPhaseIndex; }

	UFUNCTION(BlueprintPure, Category = "Magician|Attack")
	float GetCurrentPhaseMovementSpeed() const;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void StartSegment(int32 SegmentIndex);
	void SpawnOrb();
	void OnSegmentComplete();
	void OnPhaseComplete();

	AActor* FindTarget() const;
	FVector GetSpawnLocation() const;
	FRotator GetSpawnRotation(const FVector& SpawnLocation, AActor* Target) const;

	// State
	bool bIsAttacking = false;
	int32 CurrentPhaseIndex = 0;
	int32 CurrentSegmentIndex = 0;
	int32 CurrentOrbIndex = 0;

	// Cached current segment for spawning
	FMagicianPhaseSegment CurrentSegment;

	// Timers
	FTimerHandle OrbSpawnTimerHandle;
};
