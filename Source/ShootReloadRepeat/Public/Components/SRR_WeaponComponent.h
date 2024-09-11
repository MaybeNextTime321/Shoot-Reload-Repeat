// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SRR_WeaponComponent.generated.h"

class ASRRBaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTRELOADREPEAT_API USRR_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USRR_WeaponComponent();

	void SpawnWeapon();
	void DestructWeapon();
protected:
	virtual void BeginPlay() override;



	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray <TSubclassOf<ASRRBaseWeapon>> Weapons;


	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ASRRBaseWeapon> DefaultWeapon;

private:
	TArray<ASRRBaseWeapon*> SpawnedWeapon;

	ASRRBaseWeapon* CurrentWeapon;

};
