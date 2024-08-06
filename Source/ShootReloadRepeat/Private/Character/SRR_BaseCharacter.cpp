
#include "Character/SRR_BaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SRRHealthComponent.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/CharacterMovementComponent.h"

ASRR_BaseCharacter::ASRR_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	ArmComponeent = CreateDefaultSubobject<USpringArmComponent>("Arm Component");
	ArmComponeent->bUsePawnControlRotation = true;
	ArmComponeent->SetupAttachment(GetRootComponent());
	ArmComponeent->SocketOffset = FVector(-100, 100, 100);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	CameraComponent->SetupAttachment(ArmComponeent, ArmComponeent->SocketName);

	HealthComponent = CreateDefaultSubobject<USRRHealthComponent>("Health Component");
	HealthComponent->SetIsReplicated(true);
	HealthComponent->OnDeathDelegate.AddUObject(this, &ASRR_BaseCharacter::OnDeath);
}

float ASRR_BaseCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ReturnValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (HealthComponent)
	{
		ReturnValue = HealthComponent->TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	}
	UE_LOG(LogTemp, Error, TEXT("Got Damage"));
	return ReturnValue;
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

void ASRR_BaseCharacter::Force_Implementation()
{
	FVector LaunchVector = GetActorForwardVector() * ForceValue;
	if (!GetVelocity().IsNearlyZero())
	{
		LaunchVector = GetVelocity().GetSafeNormal() * ForceValue;
	}
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

float ASRR_BaseCharacter::GetMovementDegree() const
{
	const FVector VelocityNormal = GetVelocity().GetSafeNormal();
	const FVector ForwardVector = GetActorForwardVector();

	const float Degree = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(ForwardVector, VelocityNormal)));
	const float Sign = FMath::Sign(FVector::CrossProduct(ForwardVector, VelocityNormal).Z);

	return Degree * Sign;
}

void ASRR_BaseCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), FMath::Clamp(Value, -1.0f, 1.0f));
}

void ASRR_BaseCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), FMath::Clamp(Value, -1.0f, 1.0f));
}

void ASRR_BaseCharacter::OnDeath()
{

	if (GetLocalRole() == ROLE_Authority)
	{
		SetLifeSpan(3.0f);
		GetCharacterMovement()->DisableMovement();
	}
	else
	{
		PlayAnimMontage(DeathAnimation);
	}
}

