// Copyright Epic Games, Inc. All Rights Reserved.

#include "XXIICharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "XXII.h"

AXXIICharacter::AXXIICharacter()
{
	// Set size for collision capsule
	// GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	//
	// // Don't rotate when the controller rotates. Let that just affect the camera.
	// bUseControllerRotationPitch = false;
	// bUseControllerRotationYaw = false;
	// bUseControllerRotationRoll = false;
	//
	// // Configure character movement
	// GetCharacterMovement()->bOrientRotationToMovement = true;
	// GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	//
	// // Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// // instead of recompiling to adjust them
	// GetCharacterMovement()->JumpZVelocity = 500.f;
	// GetCharacterMovement()->AirControl = 0.35f;
	// GetCharacterMovement()->MaxWalkSpeed = 500.f;
	// GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	// GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	// GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	//
	// // Create a camera boom (pulls in towards the player if there is a collision)
	// CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	// CameraBoom->SetupAttachment(RootComponent);
	// CameraBoom->TargetArmLength = 400.0f;
	// CameraBoom->bUsePawnControlRotation = true;
	//
	// // Create a follow camera
	// FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	// FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// FollowCamera->bUsePawnControlRotation = false;

	CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
	CombatComponent->RegisterComponent();

	PapercutterComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("SkeletalChild"));
	PapercutterComponent->SetupAttachment(GetMesh());

	if (APapercutter* PapercutterRef = Cast<APapercutter>(PapercutterComponent->GetChildActor()))
	{
		Papercutter = PapercutterRef;
	}
}

void AXXIICharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AXXIICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	OnDashMontageEnded.BindUObject(this, &AXXIICharacter::DashMontageEnded);
}

void AXXIICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
	// 	EnhancedInputComponent->BindAction(SlashAction, ETriggerEvent::Started, this, &AXXIICharacter::Slash);
	// }
	// else
	// {
	// 	UE_LOG(LogXXII, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	// }
}

void AXXIICharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void AXXIICharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void AXXIICharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	HasDashed = false;
	SetJumpTrailState(false);
}


void AXXIICharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void AXXIICharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AXXIICharacter::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void AXXIICharacter::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}

void AXXIICharacter::DoDash()
{
	// ignore the input if we've already dashed and have yet to reset
	if (HasDashed)
		return;

	// Rotate towards the input to orient the dash in the input direction
	if (RotateBeforeDash)
	{
		SetActorRotation(GetPendingMovementInputVector().ToOrientationRotator());
	}
	
	// raise the dash flags
	IsDashing = true;
	HasDashed = true;

	// disable gravity while dashing
	GetCharacterMovement()->GravityScale = 0.0f;

	// reset the character velocity so we don't carry momentum into the dash
	GetCharacterMovement()->Velocity = FVector::ZeroVector;

	// enable the jump trails
	SetJumpTrailState(true);

	// play the dash montage
	if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
	{
		const float MontageLength = AnimInstance->Montage_Play(DashMontage, 1.0f, EMontagePlayReturnType::MontageLength, 0.0f, true);

		// has the montage played successfully?
		if (MontageLength > 0.0f)
		{
			//AnimInstance->Montage_SetEndDelegate(OnDashMontageEnded, DashMontage);
			AnimInstance->Montage_SetBlendingOutDelegate(OnDashMontageEnded, DashMontage);
		}
	}
}

void AXXIICharacter::EndDash()
{
	GetCharacterMovement()->GravityScale = 2.5f;
	
	IsDashing = false;

	// are we grounded after the dash?
	if (GetCharacterMovement()->IsMovingOnGround())
	{
		// reset the dash usage flag, since we won't receive a landed event
		HasDashed = false;

		// deactivate the jump trails
		SetJumpTrailState(false);
	}
}

void AXXIICharacter::DashMontageEnded(UAnimMontage* Montage, bool Interrupted)
{
	EndDash();
}