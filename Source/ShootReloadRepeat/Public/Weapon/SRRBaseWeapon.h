#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SRRBaseWeapon.generated.h"

UCLASS()
class SHOOTRELOADREPEAT_API ASRRBaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	ASRRBaseWeapon();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	float ShootDistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 Clips;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 Bullet;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 DamageAmount;
};
