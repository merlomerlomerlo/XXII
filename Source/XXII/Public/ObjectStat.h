// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectStat.generated.h"

USTRUCT(BlueprintType)
struct FObjectStat
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float MaxHP = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float HP = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	TArray<float> MaxStaminaSegments {0, 0, 0};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat")
	float CurrentMaxStamina = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float Stamina = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float Attack = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float Speed = 0;
};
