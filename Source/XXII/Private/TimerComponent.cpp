#include "TimerComponent.h"

UTimerComponent::UTimerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UTimerComponent::StartTimer()
{
	TimerValue = 0;
	TimerStarted = true;
	TimerFinished = false;
	SecondaryTimerFinished = false;
}

void UTimerComponent::StopTimer()
{
	TimerStarted = false;
}

// Called when the game starts
void UTimerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	TimerFinished = false;
	SecondaryTimerFinished = false;
	TimerValue = 0.f;
}

void UTimerComponent::BroadcastTimerFinished()
{
	OnTimerFinished.Broadcast();
	OnTimerFinishedBP.Broadcast();
}

void UTimerComponent::BroadcastSecondaryTimerFinished()
{
	OnSecondaryTimerFinished.Broadcast();
	OnSecondaryTimerFinishedBP.Broadcast();
}

void UTimerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!TimerStarted) return;

	TimerValue += DeltaTime;
	if (TimerValue >= TimerDuration)
	{
		TimerStarted = false;
		TimerFinished = true;
		BroadcastTimerFinished();
	}
	if (SecondaryTimerDuration == 0) return;

	if (!SecondaryTimerFinished && TimerValue >= SecondaryTimerDuration)
	{
		SecondaryTimerFinished = true;
		BroadcastSecondaryTimerFinished();
	}
}

