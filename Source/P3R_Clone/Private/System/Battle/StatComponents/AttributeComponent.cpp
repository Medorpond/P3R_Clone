#include "System/Battle/StatComponents/AttributeComponent.h"


UAttributeComponent::UAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	bBroadcastChange = true;
	for (const EP3R_StatType StatType : TEnumRange<EP3R_StatType>())
	{
		StatMap.Emplace(StatType, FStat());
		StatEventMap.Emplace(StatType, FOnStatChange());
	}
}

void UAttributeComponent::RemoveStatListener(const EP3R_StatType InType, const FDelegateHandle InHandle)
{
	FOnStatChange& Delegate = StatEventMap.FindChecked(InType);
	Delegate.Remove(InHandle);
}

void UAttributeComponent::BroadcastStatChange(const EP3R_StatType InType, const float NewValue)
{
	if (!bBroadcastChange) return;
	
	const FOnStatChange& Delegate = StatEventMap.FindChecked(InType);
	Delegate.Broadcast(NewValue);
}

void UAttributeComponent::BroadcastAll()
{
	if (!bBroadcastChange) return;
	
	for (const auto& [StatType, Delegate] : StatEventMap)
	{
		Delegate.Broadcast(GetStat(StatType));
	}
}

void UAttributeComponent::InitStats(const TArray<FStatInitPayload>& Payloads)
{
	bBroadcastChange = false;
	TArray<TPair<EP3R_StatType, FStat*>> StatToInitCache;
	
	for (const auto& [StatType, InitValue] : Payloads)
	{
		FStat& Stat = StatMap.FindChecked(StatType);
		Stat.Base = InitValue;
		
		StatToInitCache.Emplace(StatType, &Stat);
	}
	
	for (const auto [StatType, Stat] : StatToInitCache)
	{
		ClampStat(StatType, Stat->Base);
		const float CurrentValue = Stat->UpdateCurrent();
		
		UpdateDerivedStats(StatType, CurrentValue);
	}
	
	bBroadcastChange = true;
	BroadcastAll();
}

float UAttributeComponent::GetStat(const EP3R_StatType InType) const
{
	const FStat& Stat = StatMap.FindChecked(InType);
	return Stat.Current;
}


float UAttributeComponent::GetStatBase(const EP3R_StatType InType) const
{
	const FStat& Stat = StatMap.FindChecked(InType);
	return Stat.Base;
}


const FStat& UAttributeComponent::SetStatBase(const EP3R_StatType InType, float InValue)
{
	FStat& Stat = StatMap.FindChecked(InType);
	
	ClampStat(InType, InValue);
	
	Stat.Base = InValue;
	const float CurrentValue = Stat.UpdateCurrent();
	
	UpdateDerivedStats(InType, CurrentValue);
	BroadcastStatChange(InType, CurrentValue);
	
	return Stat;
}

void UAttributeComponent::ClampStat(const EP3R_StatType& StatType, float& NewValue) const
{
	
	switch (StatType)
	{
	case EP3R_StatType::HP:
		NewValue = FMath::Clamp(NewValue, 0.f, GetStat(EP3R_StatType::MaxHP));
		break;
	case EP3R_StatType::MaxHP:
		NewValue = FMath::Max(NewValue, 1.f);
		break;
	case EP3R_StatType::SP:
		NewValue = FMath::Clamp(NewValue, 0.f, GetStat(EP3R_StatType::MaxSP));
		break;
	case EP3R_StatType::MaxSP:
		NewValue = FMath::Max(NewValue, 1.f);
		break;
	default:
		break;
	}
	
}

// 사이클 발생으로 인한 무한 재귀에 주의하라. 명시적인 그래프를 먼저 확인할 것.
void UAttributeComponent::UpdateDerivedStats(const EP3R_StatType& StatType, const float NewValue)
{
	switch (StatType)
	{
	case EP3R_StatType::MaxHP:
		if (NewValue < GetStat(EP3R_StatType::HP))
		{
			SetStatBase(EP3R_StatType::HP, NewValue);
		}
		break;
	case EP3R_StatType::MaxSP:
		if (NewValue < GetStat(EP3R_StatType::SP))
		{
			SetStatBase(EP3R_StatType::SP, NewValue);
		}
		break;
	default:
		break;
	}
}

