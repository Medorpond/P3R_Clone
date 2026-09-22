// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "System/Battle/StatComponents/StatTypes.h"

#include "AttributeComponentTestListener.generated.h"


USTRUCT()
struct FRecordedStatEvent
{
	GENERATED_BODY()

	EP3R_StatType StatType = EP3R_StatType::HP;
	float Value = 0.f;
};

UCLASS()
class P3R_CLONE_API UAttributeComponentTestListener : public UObject
{
	GENERATED_BODY()

public:
	TArray<FRecordedStatEvent> Events;

	void OnHPChanged(float NewValue)
	{
		Events.Add({ EP3R_StatType::HP, NewValue });
	}

	void OnMaxHPChanged(float NewValue)
	{
		Events.Add({ EP3R_StatType::MaxHP, NewValue });
	}

	void OnSPChanged(float NewValue)
	{
		Events.Add({ EP3R_StatType::SP, NewValue });
	}

	void OnMaxSPChanged(float NewValue)
	{
		Events.Add({ EP3R_StatType::MaxSP, NewValue });
	}

	void ClearEvents()
	{
		Events.Reset();
	}
};