#include "Weapon/SRRBaseWeapon.h"

ASRRBaseWeapon::ASRRBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Skeletal Mesh");
	SetRootComponent(WeaponMesh);

}

void ASRRBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

