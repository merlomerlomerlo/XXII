// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimerComponent.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

UENUM(BlueprintType)
enum class EComboState : uint8
{
	None UMETA(DisplayName = "None"),
	Attack1 UMETA(DisplayName = "Attack1"),
	Attack2 UMETA(DisplayName = "Attack2"),
	Attack3 UMETA(DisplayName = "Attack3")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class XXII_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatComponent();

	UPROPERTY()
	class AXXIICharacter* Owner;

	UPROPERTY()
	UAnimInstance* AnimInstance;

	// SHOOTING

	UFUNCTION(BlueprintCallable, Category="Shoot")
	void StartAiming();
	
	UFUNCTION(BlueprintCallable, Category="Shoot")
	void StopAiming();

	UFUNCTION(BlueprintCallable, Category="Shoot")
	void Shoot();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Shoot")
	float TempCharacterSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Shoot")
	bool IsAiming = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Shoot")
	bool IsShooting = false;

	UFUNCTION(BlueprintCallable, Category="Slash")
	void Handle_ShootProjectile();

	// SLASHING

	UFUNCTION(BlueprintCallable, Category="Slash")
	void StartSlash();

	UFUNCTION(BlueprintCallable, Category="Slash")
	void QueueAttack();

	UFUNCTION(BlueprintCallable, Category="Slash")
	void ReleaseAttack();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Slash")
	bool AttackQueued = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Slash")
	bool AttackPressed = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Slash")
	bool CanQueueAttack = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Slash")
	EComboState ComboState = EComboState::None;

	UPROPERTY(EditAnywhere, Category="Slash")
	UAnimMontage* SlashMontage;

	FOnMontageEnded OnSlashMontageEnded;

	void SlashMontageEnded(UAnimMontage* Montage, bool Interrupted);

	UPROPERTY(EditAnywhere, Category="Slash")
	FName Attack2SectionName;

	UPROPERTY(EditAnywhere, Category="Slash")
	FName Attack3SectionName;

	UFUNCTION(BlueprintCallable, Category="Slash")
	void Handle_ComboWindowStart();

	UFUNCTION(BlueprintCallable, Category="Slash")
	void Handle_ComboWindowEnd();

	UFUNCTION(BlueprintCallable, Category="Slash")
	void Handle_HeavyAttackWindowEnd();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
