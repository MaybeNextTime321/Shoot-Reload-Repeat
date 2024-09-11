#include "Components/SRR_WeaponComponent.h"
#include  "Weapon/SRRBaseWeapon.h"
#include "GameFramework/Character.h"

USRR_WeaponComponent::USRR_WeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;


}

void USRR_WeaponComponent::SpawnWeapon()
{
	if (!GetWorld())
	{
		return;
	}
	ACharacter* Owner = Cast <ACharacter>(GetOwner());

	if (!Owner)
	{
		return;
	}

	for (auto SpawningWeapon : Weapons)
	{
		const auto SpawnedSingleWeapon = GetWorld()->SpawnActor<ASRRBaseWeapon>(SpawningWeapon);
		SpawnedSingleWeapon->SetOwner(Owner);
		if (SpawnedSingleWeapon)
		{
			SpawnedSingleWeapon->AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false), "WeaponSoket");
			SpawnedWeapon.Add(SpawnedSingleWeapon);
			CurrentWeapon = SpawnedSingleWeapon;
		}
		
	}
}

void USRR_WeaponComponent::DestructWeapon()
{
	if (!GetWorld())
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Destruct Weapon"));

	for (auto Weapon : SpawnedWeapon)
	{
		GetWorld()->DestroyActor(Weapon);
	}
}


void USRR_WeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	SpawnWeapon();
	
}
