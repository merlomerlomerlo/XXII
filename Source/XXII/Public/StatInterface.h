// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectStat.h"
#include "UObject/Interface.h"
#include "StatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UStatInterface : public UInterface
{
	GENERATED_BODY()
};


class XXII_API IStatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Stat")
	FObjectStat GetStat();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Stat")
	void SetStat(FObjectStat Stat);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Stat|HP")
	void Damage(float DamageAmount);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Stat|HP")
	void Heal(float HealAmount);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Stat|MaxHP")
	void SetMaxHP(float MaxHP);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Stat|MaxMP")
	void IncreaseMaxHP(float IncrementAmount);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Stat|MaxMP")
	void DecreaseMaxHP(float DecreaseAmount);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Stat|Stamina")
	void ConsumeStamina(float StaminaAmount);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Stat|Stamina")
	bool TryConsumeStamina(float StaminaAmount);
};
