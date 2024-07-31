
#include "Character/SRR_BaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ASRR_BaseCharacter::ASRR_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	ArmComponeent = CreateDefaultSubobject<USpringArmComponent>("Arm Component");
	ArmComponeent->bUsePawnControlRotation = true;
	ArmComponeent->SetupAttachment(GetRootComponent());
	ArmComponeent->SocketOffset = FVector(-100, 100, 100);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	CameraComponent->SetupAttachment(ArmComponeent, ArmComponeent->SocketName);

}

void ASRR_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASRR_BaseCharacter::Jump()
{
		Super::Jump();
}

void ASRR_BaseCharacter::StopJumping()
{
	Super::StopJumping();
}

void ASRR_BaseCharacter::Force()
{
	FVector LaunchVector = GetActorRotation().Vector().GetSafeNormal() * ForceValue;
	LaunchCharacter(LaunchVector, false, true);
}

void ASRR_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Move Forward", this, &ASRR_BaseCharacter::MoveForward);
	InputComponent->BindAxis("Move Right", this, &ASRR_BaseCharacter::MoveRight);
	InputComponent->BindAxis("Look Up", this, &ASRR_BaseCharacter::AddControllerPitchInput);
	InputComponent->BindAxis("Look Right", this, &ASRR_BaseCharacter::AddControllerYawInput);
	InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ASRR_BaseCharacter::Jump);
	InputComponent->BindAction("Force", EInputEvent::IE_Pressed, this, &ASRR_BaseCharacter::Force);
}

void ASRR_BaseCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), FMath::Clamp(Value, -1.0f, 1.0f));
}

void ASRR_BaseCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), FMath::Clamp(Value, -1.0f, 1.0f));
}

