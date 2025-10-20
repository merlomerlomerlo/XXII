// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectStat.generated.h"

USTRUCT(BlueprintType)
struct FObjectStat
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float MaxHP = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float HP = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float MaxStamina = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float Stamina = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float Attack = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float Speed = 0;
};
