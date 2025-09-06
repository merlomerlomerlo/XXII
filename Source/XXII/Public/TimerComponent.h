// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FTimerFinishedDelegate);
DECLARE_MULTICAST_DELEGATE(FSecondaryTimerFinishedDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTimerFinishedDelegateBP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSecondaryTimerFinishedDelegateBP);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class XXII_API UTimerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTimerComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Timer", meta=(ClampMin = 0))
	float TimerDuration = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Timer", meta=(ClampMin = 0))
	float SecondaryTimerDuration = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Timer")
	float TimerValue = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Timer")
	bool TimerFinished = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Timer")
	bool SecondaryTimerFinished = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Timer")
	bool TimerStarted = false;

	UFUNCTION(BlueprintCallable, Category="Timer")
	void StartTimer();

	UFUNCTION(BlueprintCallable, Category="Timer")
	void StopTimer();

	FTimerFinishedDelegate OnTimerFinished;
	FSecondaryTimerFinishedDelegate OnSecondaryTimerFinished;

	UPROPERTY(BlueprintAssignable)
	FTimerFinishedDelegateBP OnTimerFinishedBP;

	UPROPERTY(BlueprintAssignable)
	FSecondaryTimerFinishedDelegateBP OnSecondaryTimerFinishedBP;
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void BroadcastTimerFinished();
	void BroadcastSecondaryTimerFinished();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
