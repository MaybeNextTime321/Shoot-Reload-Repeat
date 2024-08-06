#include "Components/SRRHealthComponent.h"
#include "Net/UnrealNetwork.h"
#include "Character/SRR_BaseCharacter.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

USRRHealthComponent::USRRHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USRRHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USRRHealthComponent, CurrentHealth)
}

bool USRRHealthComponent::IsDead() const
{
	return FMath::IsNearlyZero(CurrentHealth);
}

void USRRHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (MaxHealth == 0.0f)
	{
		MaxHealth = 100.0f;
	}

	CurrentHealth = MaxHealth;
	
}

void USRRHealthComponent::OnDeath()
{
	OnDeathDelegate.Broadcast();
}

void USRRHealthComponent::OnHealthChange()
{
	const auto Owner = Cast<ASRR_BaseCharacter>(GetOwner());
	if (!Owner)
	{
		return;
	}

	if (Owner->GetLocalRole() == ROLE_Authority)
	{
		FString HealthMessage = FString::Printf(TEXT("Server actor %s have %f health remaining"), *Owner->GetName(),CurrentHealth);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, HealthMessage);
	}

	if (Owner->IsLocallyControlled())
	{
		FString HealthMessage = FString::Printf(TEXT("You now have %f health remaining"), CurrentHealth);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, HealthMessage);

		if (FMath::IsNearlyZero(CurrentHealth))
		{
			FString DeathMessage = FString::Printf(TEXT("You are die"));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, DeathMessage);
		}
	}

	if (IsDead())
	{
		OnDeath();
	}
}

void USRRHealthComponent::SetCurrentHealth(float NewCurrentHealth)
{
	if (!GetOwner() || IsDead())
	{
		return;
	}

	if (GetOwner()->GetLocalRole() == ROLE_Authority)
	{
		CurrentHealth = FMath::Clamp(NewCurrentHealth, 0.0f, MaxHealth);
		OnHealthChange();
	}
}

float USRRHealthComponent::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float NewHealth = CurrentHealth - Damage;
	SetCurrentHealth(NewHealth);

	return NewHealth;
}

void USRRHealthComponent::OnRep_CurrentHealth()
{
	OnHealthChange();
}
