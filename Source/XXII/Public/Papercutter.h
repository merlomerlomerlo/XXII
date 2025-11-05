// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Papercutter.generated.h"

UCLASS()
class XXII_API APapercutter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APapercutter();

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* PapercutterMesh;

	UPROPERTY(EditAnywhere)
	TArray<FName> PapercutterBones;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
