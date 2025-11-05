// Fill out your copyright notice in the Description page of Project Settings.


#include "Papercutter.h"

// Sets default values
APapercutter::APapercutter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	PapercutterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PaperCutterMesh"));
	RootComponent = PapercutterMesh;
}

// Called when the game starts or when spawned
void APapercutter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APapercutter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

