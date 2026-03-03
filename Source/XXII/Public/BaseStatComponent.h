// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseStatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLifeDelegate, float, _HP, float, NormalizedHP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathDelegate);

UCLASS( ClassGroup=(Custom),Blueprintable ,meta=(BlueprintSpawnableComponent) )
class XXII_API UBaseStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	float _HP;
	virtual void _SetHP(float InHP);
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat|HP", meta=(ClampMin="1", UIMin="1"))
	float MaxHP = 3;

	UPROPERTY(EditAnywhere, BlueprintSetter=SetHP, Category = "Stat|HP", meta=(ClampMin="0", UIMin="0"))
	float HP = 3;
	
	UFUNCTION(BlueprintSetter, Category = "Stat|HP")
	void SetHP(float InHP);

	UFUNCTION(BlueprintImplementableEvent, Category = "Stat|HP")
	void OnChangeHPEvent(float InHP, float NormalizedHP);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "Stat|HP")
	void Heal(float HealAmount);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Stat|HP")
	void Damage(float DamageAmount);
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="Stat|Event")
	FLifeDelegate OnChangeHP;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="Stat|Event")
	FDeathDelegate OnDeath;
};
