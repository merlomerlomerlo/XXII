// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"
#include "Projectile.h"
#include "XXIICharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "StatInterface.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	AXXIICharacter* OwnerCharacter = Cast<AXXIICharacter>(GetOwner());

	if (OwnerCharacter)
	{
		Owner = OwnerCharacter;
		USkeletalMeshComponent* MeshComp = Owner->GetMesh();
		if (MeshComp)
		{
			AnimInstance = MeshComp->GetAnimInstance();
		}
	}
	
	OnSlashMontageEnded.BindUObject(this, &UCombatComponent::SlashMontageEnded);
}


// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCombatComponent::StartAiming()
{
	TempCharacterSpeed = Owner->GetCharacterMovement()->MaxWalkSpeed;
	Owner->GetCharacterMovement()->MaxWalkSpeed = 0;
	IsAiming = true;
}

void UCombatComponent::StopAiming()
{
	Owner->GetCharacterMovement()->MaxWalkSpeed = TempCharacterSpeed;
	IsAiming = false;
	IsShooting = false;
}

void UCombatComponent::Shoot()
{
	IsShooting = true;
}

void UCombatComponent::Handle_ShootProjectile()
{
	FVector SpawnLocation = Owner->GetActorLocation();
	FVector Forward = Owner->GetActorForwardVector();
	
	if (AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(AProjectile::StaticClass()))
	{
		Projectile->InitProjectile(SpawnLocation, Forward);
	}
}

void UCombatComponent::StartSlash()
{
	if (!Owner || !AnimInstance) return;

	if (ComboState == EComboState::None)
	{
		const float MontageLength = AnimInstance->Montage_Play(SlashMontage, 1.0f, EMontagePlayReturnType::MontageLength, 0.0f, true);
		if (MontageLength > 0.0f)
		{
			ComboState = EComboState::Attack1;
			AnimInstance->Montage_SetEndDelegate(OnSlashMontageEnded, SlashMontage);
		}
	}
	else if (ComboState == EComboState::Attack1)
	{
		ComboState = EComboState::Attack2;
		AnimInstance->Montage_JumpToSection(Attack2SectionName, SlashMontage);
	}
	else if (ComboState == EComboState::Attack2)
	{
		ComboState = EComboState::Attack3;
		AnimInstance->Montage_JumpToSection(Attack3SectionName, SlashMontage);
	}
	if (AttackPressed) AnimInstance->Montage_Pause(SlashMontage);
}

void UCombatComponent::QueueAttack()
{
	if (GetOwner()->GetClass()->ImplementsInterface(UStatInterface::StaticClass()))
	{
		CanQueueAttack = (IStatInterface::Execute_GetStat(GetOwner()).Stamina > 0);
	}
	
	if (CanQueueAttack)
	{
		AttackPressed = true;
		if (ComboState == EComboState::None) StartSlash();
		else AttackQueued = true;
		CanQueueAttack = false;
	}
}

void UCombatComponent::ReleaseAttack()
{
	AttackPressed = false;
	AnimInstance->Montage_Resume(SlashMontage);
}

void UCombatComponent::SlashMontageEnded(UAnimMontage* Montage, bool Interrupted)
{
	CanQueueAttack = true;
	ComboState = EComboState::None;
}

void UCombatComponent::Handle_ComboWindowStart()
{
	CanQueueAttack = true;
}

void UCombatComponent::Handle_ComboWindowEnd()
{
	if (GetOwner()->GetClass()->ImplementsInterface(UStatInterface::StaticClass()))
	{
		AttackQueued = AttackQueued && (IStatInterface::Execute_GetStat(GetOwner()).Stamina > 0);
	}
	
	if (AttackQueued) StartSlash();
	AttackQueued = false;
	CanQueueAttack = false;
}

void UCombatComponent::Handle_HeavyAttackWindowEnd()
{
	ReleaseAttack();
}
