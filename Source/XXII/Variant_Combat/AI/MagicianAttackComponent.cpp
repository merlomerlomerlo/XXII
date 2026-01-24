#include "MagicianAttackComponent.h"
#include "MagicianOrb.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

UMagicianAttackComponent::UMagicianAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMagicianAttackComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMagicianAttackComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	StopAttackSequence();
	Super::EndPlay(EndPlayReason);
}

void UMagicianAttackComponent::StartAttackSequence()
{
	if (Phases.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("MagicianAttackComponent: No phases configured"));
		return;
	}

	bIsAttacking = true;
	StartPhase(0);
}

void UMagicianAttackComponent::StopAttackSequence()
{
	bIsAttacking = false;
	GetWorld()->GetTimerManager().ClearTimer(OrbSpawnTimerHandle);
}

void UMagicianAttackComponent::StartPhase(int32 PhaseIndex)
{
	if (!Phases.IsValidIndex(PhaseIndex))
	{
		bIsAttacking = false;
		OnAllPhasesCompleted.Broadcast();
		return;
	}

	CurrentPhaseIndex = PhaseIndex;
	CurrentSegmentIndex = 0;

	const FMagicianPhase& Phase = Phases[CurrentPhaseIndex];
	if (Phase.Segments.Num() == 0)
	{
		OnPhaseComplete();
		return;
	}

	StartSegment(0);
}

void UMagicianAttackComponent::StartSegment(int32 SegmentIndex)
{
	const FMagicianPhase& Phase = Phases[CurrentPhaseIndex];

	if (!Phase.Segments.IsValidIndex(SegmentIndex))
	{
		OnPhaseComplete();
		return;
	}

	CurrentSegmentIndex = SegmentIndex;
	CurrentOrbIndex = 0;
	CurrentSegment = Phase.Segments[CurrentSegmentIndex];

	// Spawn first orb immediately, then start timer for subsequent orbs
	SpawnOrb();
}

void UMagicianAttackComponent::SpawnOrb()
{
	if (!bIsAttacking)
	{
		return;
	}

	AActor* Target = FindTarget();
	const FVector SpawnLocation = GetSpawnLocation();
	const FRotator SpawnRotation = GetSpawnRotation(SpawnLocation, Target);

	// Choose orb class based on explosive flag
	TSubclassOf<AMagicianOrb> ClassToSpawn = CurrentSegment.bIsExplosive ? ExplosiveOrbClass : OrbClass;

	if (!ClassToSpawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("MagicianAttackComponent: No orb class set"));
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = Cast<APawn>(GetOwner());
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AMagicianOrb* Orb = GetWorld()->SpawnActor<AMagicianOrb>(
		ClassToSpawn,
		SpawnLocation,
		SpawnRotation,
		SpawnParams
	);

	if (Orb)
	{
		Orb->InitOrb(
			CurrentSegment.OrbSpeed,
			CurrentSegment.OrbDamage,
			CurrentSegment.OrbLifespanSeconds,
			CurrentSegment.bIsExplosive,
			CurrentSegment.ExplosiveOrbDamageRadius
		);
	}

	CurrentOrbIndex++;

	// Check if more orbs to spawn
	if (CurrentOrbIndex < CurrentSegment.OrbAmount)
	{
		GetWorld()->GetTimerManager().SetTimer(
			OrbSpawnTimerHandle,
			this,
			&UMagicianAttackComponent::SpawnOrb,
			CurrentSegment.OrbSpawnRate,
			false
		);
	}
	else
	{
		OnSegmentComplete();
	}
}

void UMagicianAttackComponent::OnSegmentComplete()
{
	OnSegmentCompleted.Broadcast(CurrentSegmentIndex);

	// Move to next segment
	StartSegment(CurrentSegmentIndex + 1);
}

void UMagicianAttackComponent::OnPhaseComplete()
{
	OnPhaseCompleted.Broadcast();

	// Move to next phase
	StartPhase(CurrentPhaseIndex + 1);
}

float UMagicianAttackComponent::GetCurrentPhaseMovementSpeed() const
{
	if (Phases.IsValidIndex(CurrentPhaseIndex))
	{
		return Phases[CurrentPhaseIndex].MovementSpeed;
	}
	return 0.f;
}

AActor* UMagicianAttackComponent::FindTarget() const
{
	// Find player character as target
	return UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}

FVector UMagicianAttackComponent::GetSpawnLocation() const
{
	// Spawn from owner's location, slightly forward and up
	if (AActor* Owner = GetOwner())
	{
		const FVector Forward = Owner->GetActorForwardVector();
		return Owner->GetActorLocation() + Forward * 100.f + FVector::UpVector * 50.f;
	}
	return FVector::ZeroVector;
}

FRotator UMagicianAttackComponent::GetSpawnRotation(const FVector& SpawnLocation, AActor* Target) const
{
	if (Target)
	{
		// Aim at target
		const FVector Direction = (Target->GetActorLocation() - SpawnLocation).GetSafeNormal();
		return Direction.Rotation();
	}

	// Default to owner's forward direction
	if (AActor* Owner = GetOwner())
	{
		return Owner->GetActorRotation();
	}

	return FRotator::ZeroRotator;
}
