
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SRR_BaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class SHOOTRELOADREPEAT_API ASRR_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASRR_BaseCharacter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* ArmComponeent;

	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere)
	FVector ForceValue;

	virtual void Jump() override;

	virtual void StopJumping() override;

	UFUNCTION(BlueprintCallable, Category = Character)
	void Force();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementDegree()const;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
};
