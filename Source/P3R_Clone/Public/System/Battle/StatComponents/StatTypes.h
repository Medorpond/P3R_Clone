#pragma once

#include "CoreMinimal.h"
#include "StatTypes.generated.h"

struct FStat;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnStatChange, float);


UENUM(BlueprintType)
enum class EP3R_StatType : uint8
{
	HP		UMETA(DisplayName = "Health Point"),
	MaxHP	UMETA(DisplayName = "Max Health Point"),
	SP		UMETA(DisplayName = "Skill Point"),
	MaxSP	UMETA(DisplayName = "Max Skill Point"),
	ATK		UMETA(DisplayName = "Attack Point"),
	DEF		UMETA(DisplayName = "Defence Point"),
	CRT		UMETA(DisplayName = "Critical Rate"),
	EVA		UMETA(DisplayName = "Evasion Rate"),
	ACC		UMETA(DisplayName = "Accuracy"),
	ALR		UMETA(DisplayName = "Ailment Resistance"),
	
	Count	UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(EP3R_StatType, EP3R_StatType::Count);

USTRUCT(BlueprintType)
struct FStat
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, Category = "Value")
	float Base = 0.f;
	UPROPERTY(VisibleAnywhere, Category = "Value")
	float Current = 0.f;
	
	// TODO: 나중에 API 뚫어주기
	UPROPERTY(VisibleAnywhere, Category = "Modifier")
	float Additive = 0.f;
	UPROPERTY(VisibleAnywhere, Category = "Modifier")
	float Multiplier = 1.f;
	
	float UpdateCurrent() { return Current = (Base + Additive) * Multiplier; }
};
