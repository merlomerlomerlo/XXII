// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent.h"

#if WITH_EDITOR
void UStatComponent::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	const FName ChangedPropertyName = (PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None);
	
	if (ChangedPropertyName == GET_MEMBER_NAME_CHECKED(UStatComponent, MaxHP) || ChangedPropertyName == GET_MEMBER_NAME_CHECKED(UStatComponent, MaxStaminaSegments))
	{
		MaxStaminaSegments.SetNum(MaxHP);
	}
	else if (ChangedPropertyName == GET_MEMBER_NAME_CHECKED(UStatComponent, HP))
	{
		RefreshCurrentMaxStamina();
	}
	
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

// Sets default values for this component's properties
UStatComponent::UStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UStatComponent::BeginPlay()
{
	Super::BeginPlay();
	OnChangeHP.AddDynamic(this, &UStatComponent::OnChangeHPEvent);
}


// Called every frame
void UStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UStatComponent::_SetHP(float InHP)
{
	HP = InHP;
	if (HP <= 0)
	{
		OnDeath.Broadcast();
	}
	else
	{
		RefreshCurrentMaxStamina();
		OnChangeHP.Broadcast(HP, HP/MaxHP);
	}
}

void UStatComponent::RefreshCurrentMaxStamina_Implementation()
{
	float LocalStamina = 0;
	for (int32 i = 0; i < MaxHP + 1 - HP; i++)
	{
		if (MaxStaminaSegments.IsValidIndex(i))
		{
			LocalStamina += MaxStaminaSegments[i];
		}
	}
	
	CurrentMaxStamina = LocalStamina;
}




