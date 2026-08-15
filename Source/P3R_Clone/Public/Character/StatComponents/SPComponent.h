#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SPComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSPChanged, float, NewSP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxSPChanged, float, NewMaxSP);

UCLASS(ClassGroup=(Custom))
class P3R_CLONE_API USPComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USPComponent();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnSPChanged OnSPChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnMaxSPChanged OnMaxSPChanged;
	
public:
	float GetSP() const { return SP; }
	float GetMaxSP() const { return MaxSP; }
	
	FORCEINLINE void IncreaseSP(float Delta) { SetSP(SP + Delta); }
	FORCEINLINE void DecreaseSP(float Delta) { SetSP(SP - Delta); }
	/** API wrapper method. Use Setter inside this class instead.*/
	FORCEINLINE void OverwriteSP(float InSP) { SetSP(InSP); }
	FORCEINLINE void OverwriteMaxSP(float InMaxSP) { SetMaxSP(InMaxSP); }
	
	
protected:
	void SetSP(float InSP);
	void SetMaxSP(float InMaxSP);
	
	FORCEINLINE float ClampSP(float InSP) const
	{ return FMath::RoundToFloat(FMath::Clamp(InSP, 0.f, MaxSP)); }
	
	FORCEINLINE float ClampMaxSP(float InMaxSP) const
	{ return FMath::RoundToFloat(FMath::Max(InMaxSP, 1.f)); }
	
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats|SP", 
	meta = (ClampMin = "1.0", UIMin = "1.0", AllowPrivateAccess = "true"))
	float SP = 100.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats|SP", 
	meta = (ClampMin = "1.0", UIMin = "1.0", AllowPrivateAccess = "true"))
	float MaxSP = 100.f;
};
