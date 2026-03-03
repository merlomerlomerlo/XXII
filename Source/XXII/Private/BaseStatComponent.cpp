// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseStatComponent.h"

#include "HLSLMathAliases.h"

// Sets default values for this component's properties
UBaseStatComponent::UBaseStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBaseStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBaseStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBaseStatComponent::SetHP(float InHP)
{
	_SetHP(InHP);
}

void UBaseStatComponent::Damage_Implementation(float DamageAmount)
{
	_SetHP(FMath::Max(HP - FMath::Abs(DamageAmount), 0.0f));
}

void UBaseStatComponent::Heal_Implementation(float HealAmount)
{
	_SetHP(FMath::Min(HP + FMath::Abs(HealAmount), MaxHP));
}

void UBaseStatComponent::_SetHP(float InHP)
{
	HP = InHP;
	if (HP <= 0)
	{
		OnDeath.Broadcast();
	}
	else
	{
		OnChangeHP.Broadcast(HP, HP/MaxHP);
	}
}


