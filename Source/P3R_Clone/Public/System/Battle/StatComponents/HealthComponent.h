#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChanged, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthDepleted);

UCLASS(ClassGroup=(StatComponent))
class P3R_CLONE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();
	
protected:
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnMaxHealthChanged OnMaxHealthChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthDepleted OnHealthDepleted;
	
public:
	float GetHealth() const { return Health; }
	float GetMaxHealth() const { return MaxHealth; }
	
	
	FORCEINLINE void IncreaseHealth(float Delta) { SetHealth(Health + Delta); }
	FORCEINLINE void DecreaseHealth(float Delta) { SetHealth(Health - Delta); }
	/** API wrapper method. Use Setter inside this class instead.*/
	FORCEINLINE void OverwriteHealth(float InHealth) { SetHealth(InHealth); }
	FORCEINLINE void OverwriteMaxHealth(float InMaxHealth) { SetMaxHealth(InMaxHealth); }
	
	
protected:
	void SetHealth(float InHealth);
	void SetMaxHealth(float InMaxHealth);
	
	FORCEINLINE float ClampHealth(float InHealth) const
	{ return FMath::RoundToFloat(FMath::Clamp(InHealth, 0.f, MaxHealth)); }
	
	FORCEINLINE float ClampMaxHealth(float InMaxHealth) const
	{ return FMath::RoundToFloat(FMath::Max(InMaxHealth, 1.f)); }

	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats|Health", 
		meta = (ClampMin = "1.0", UIMin = "1.0", AllowPrivateAccess = "true"))
	float Health = 100.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats|Health", 
		meta = (ClampMin = "1.0", UIMin = "1.0", AllowPrivateAccess = "true"))
	float MaxHealth = 100.f;
};
