#pragma once

#include "CoreMinimal.h"
#include "StatTypes.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"

/*
 * TODO: 
 * * TArray 방식으로 개선하는 것을 고려하라.
 * * Derived Stat 의존성이 증가할 경우 dependency graph 기반으로 리팩토링 검토
 * * 현재 프로젝트 규모에서는 switch 기반으로 유지
 */


USTRUCT(BlueprintType)
struct FStatInitPayload
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	EP3R_StatType Type = EP3R_StatType::HP;
	
	UPROPERTY(EditDefaultsOnly)
	float Value = 0.f;
};

UCLASS(ClassGroup=(StatComponent), meta=(BlueprintSpawnableComponent))
class P3R_CLONE_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAttributeComponent();
	
public:
	template<typename ListenerClass>
	FDelegateHandle AddStatListener(
		const EP3R_StatType InType,
		ListenerClass* InObject,
		void (ListenerClass::*InCallback)(float)
		);
	void RemoveStatListener(const EP3R_StatType InType, const FDelegateHandle InHandle);
	
protected:
	void BroadcastStatChange(const EP3R_StatType InType, const float NewValue);
	void BroadcastAll();
	
public:
	UFUNCTION(BlueprintCallable)
	void InitStats(const TArray<FStatInitPayload>& Payloads);
	
	UFUNCTION(BlueprintPure)
	float GetStat(const EP3R_StatType InType) const;
	UFUNCTION(BlueprintPure)
	float GetStatBase(const EP3R_StatType InType) const;
	UFUNCTION(BlueprintCallable)
	const FStat& SetStatBase(const EP3R_StatType InType, float InValue);
	
	UFUNCTION(BlueprintCallable)
	const FStat& IncreaseStatBase(const EP3R_StatType InType, const float Delta) 
	{ return SetStatBase(InType, GetStatBase(InType) + Delta); }
	UFUNCTION(BlueprintCallable)
	const FStat& DecreaseStatBase(const EP3R_StatType InType, const float Delta) 
	{ return SetStatBase(InType, GetStatBase(InType) - Delta); }

protected:
	void ClampStat(const EP3R_StatType& StatType, float& NewValue) const;
	void UpdateDerivedStats(const EP3R_StatType& StatType, const float NewValue);
	
private:
	UPROPERTY(EditAnywhere)
	TMap<EP3R_StatType, FStat> StatMap;
	TMap<EP3R_StatType, FOnStatChange> StatEventMap;
	
	bool bBroadcastChange = true;
};

#pragma region Template Method Implementation

template <typename ListenerClass>
FDelegateHandle UAttributeComponent::AddStatListener(
	const EP3R_StatType InType,
	ListenerClass* InObject,
	void(ListenerClass::* InCallback)(float))
{
	static_assert(
	TIsDerivedFrom<ListenerClass, UObject>::Value,
	"Listener Class must derive from UObject.");
	
	FOnStatChange& Delegate = StatEventMap.FindChecked(InType);
	return Delegate.AddUObject(InObject, InCallback);
}

#pragma endregion
