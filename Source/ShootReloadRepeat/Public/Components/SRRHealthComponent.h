#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SRRHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeadSignature)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTRELOADREPEAT_API USRRHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USRRHealthComponent();
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	bool IsDead() const;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetMaxHealth()const
	{
		return MaxHealth;
	}

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetCurrentHealth()const
	{
		return CurrentHealth;
	}

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetCurrentHealthPercent()const
	{
		return MaxHealth > 0 ? CurrentHealth/MaxHealth : 0;
	}

	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetCurrentHealth(float CurrentHealth);

	UFUNCTION(BlueprintCallable, Category = "Health")
	float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	
	FOnDeadSignature OnDeathDelegate;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float MaxHealth;

	UPROPERTY(ReplicatedUsing=OnRep_Currenthealth)
	float CurrentHealth;

	UFUNCTION()
	void OnRep_CurrentHealth();

	void OnHealthChange();

private:

	void OnDeath();

		
};
