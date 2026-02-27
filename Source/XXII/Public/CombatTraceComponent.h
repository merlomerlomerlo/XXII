// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatTraceComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHitDelegate, AActor*, HitActors);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class XXII_API UCombatTraceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCombatTraceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	TArray<FName> GetSocketNames() const;

	UPROPERTY()
	TArray<AActor*> FoundActors;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere/*, meta=(GetOptions="GetSocketNames")*/)
	FName StartSocket;
	
	UPROPERTY(EditAnywhere/*, meta=(GetOptions="GetSocketNames")*/)
	FName EndSocket;

	UFUNCTION(BlueprintCallable)
	void StartMelee();

	UFUNCTION(BlueprintCallable)
	void EndMelee();

	UPROPERTY(EditAnywhere)
	bool DebugSpheres = false;

	UPROPERTY(EditAnywhere)
	float SphereRadius = 5.f;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Pawn;

	UPROPERTY(BlueprintAssignable)
	FHitDelegate OnActorHit;

private:
	FVector PreviousStart = FVector::ZeroVector;
	FVector PreviousEnd = FVector::ZeroVector;

	bool IsMeleeActive = false;

	UFUNCTION()
	TArray<FHitResult> SphereTrace(FVector Start, FVector End) ;
};
