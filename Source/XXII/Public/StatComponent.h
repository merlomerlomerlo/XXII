// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStatComponent.h"
#include "Components/ActorComponent.h"
#include "StatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStaminaDelegate, float, _Stamina, float, NormalizedStamina);

UCLASS( ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent) )
class XXII_API UStatComponent : public UBaseStatComponent
{
	GENERATED_BODY()

	#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	#endif

	
public:	
	// Sets default values for this component's properties
	UStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void _SetHP(float InHP) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat|Stamina", meta=(ClampMin="1", UIMin="1"))
	TArray<float> MaxStaminaSegments {20, 20, 20};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stat|Stamina")
	float CurrentMaxStamina = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat|Stamina", meta=(ClampMin="0", UIMin="0"))
	float Stamina = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta=(ClampMin="0", UIMin="0"))
	float Attack = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta=(ClampMin="0", UI="0"));
	float Speed = 0;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Stat|Stamina")
	void OnChangeStaminaEvent(float InStamina, float NormalizedStamina);
	
	UFUNCTION(BlueprintNativeEvent, Category= "Stat|Stamina")
	void RefreshCurrentMaxStamina();

	
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="Stat|Event")
	FStaminaDelegate OnChangeStamina;
};
