
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SRR_BaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USRRHealthComponent;;
class UAnimMontage;
class USRR_WeaponComponent;

UCLASS()
class SHOOTRELOADREPEAT_API ASRR_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASRR_BaseCharacter();
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* ArmComponeent;

	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere)
	USRR_WeaponComponent* WeaponComponent;

	UPROPERTY(EditAnywhere)
	FVector ForceValue;

	UPROPERTY(EditDefaultsOnly)
	USRRHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* DeathAnimation;

	virtual void Jump() override;

	virtual void StopJumping() override;

	UFUNCTION(BlueprintCallable, Category = Character, Server, Reliable)
	void Force();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementDegree()const;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void OnDeath();
};
