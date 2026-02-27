// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatTraceComponent.h"

#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UCombatTraceComponent::UCombatTraceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCombatTraceComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

TArray<FName> UCombatTraceComponent::GetSocketNames() const
{
	TArray<FName> Names;

	if (!SkeletalMesh) return Names;

	return SkeletalMesh->GetAllSocketNames();
}


// Called every frame
void UCombatTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsMeleeActive) return;

	FVector CurrentStart = SkeletalMesh->GetSocketLocation(StartSocket);
	FVector CurrentEnd   = SkeletalMesh->GetSocketLocation(EndSocket);

	TArray<FHitResult> Hits;

	Hits.Append(SphereTrace(CurrentStart, CurrentEnd));

	if (!PreviousStart.IsZero())
	{
		Hits.Append(SphereTrace(PreviousEnd, CurrentEnd));
	}

	for (auto& Hit : Hits)
	{
		if (AActor* HitActor = Hit.GetActor())
		{
			if (!FoundActors.Contains(HitActor))
			{
				FoundActors.Add(HitActor);
				OnActorHit.Broadcast(HitActor);
			}
		}
	}

	PreviousStart = CurrentStart;
	PreviousEnd = CurrentEnd;

	
}

void UCombatTraceComponent::StartMelee()
{
	PreviousStart = FVector::ZeroVector;
	PreviousEnd = FVector::ZeroVector;

	IsMeleeActive = true;
}

void UCombatTraceComponent::EndMelee()
{
	FoundActors.Empty();

	IsMeleeActive = false;
}

TArray<FHitResult> UCombatTraceComponent::SphereTrace(FVector Start, FVector End)
{
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());
	TArray<FHitResult> TempHits;
		GetWorld()->SweepMultiByChannel(
		TempHits,
		Start,
		End,
		FQuat::Identity,
		TraceChannel,
		FCollisionShape::MakeSphere(SphereRadius),
		Params
	);

	if (DebugSpheres)
	{
		DrawDebugSphere(GetWorld(), Start, SphereRadius, 16, FColor::Green, false, DebugLifetime);
		DrawDebugSphere(GetWorld(), End,   SphereRadius, 16, FColor::Green,   false, DebugLifetime);
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, DebugLifetime, 0, 1.f);
	}

	return TempHits;
}

