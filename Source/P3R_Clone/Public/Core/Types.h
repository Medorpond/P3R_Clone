#pragma once

#include "CoreMinimal.h"
#include "Types.generated.h"

UENUM(BlueprintType)
enum class ECoreStats : uint8
{
	STR		UMETA(DisplayName = "Strength"),
	MAG		UMETA(DisplayName = "Magic"),
	END		UMETA(DisplayName = "Endurance"),
	AGI		UMETA(DisplayName = "Agility"),
	LUK		UMETA(DisplayName = "Luck")
};

USTRUCT(BlueprintType)
struct FCoreStats
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	int32 Strength;
	UPROPERTY(EditDefaultsOnly)
	int32 Magic;
	UPROPERTY(EditDefaultsOnly)
	int32 Endurance;
	UPROPERTY(EditDefaultsOnly)
	int32 Agility;
	UPROPERTY(EditDefaultsOnly)
	int32 Luck;
	
	int32 GetStat(const ECoreStats StatType) const
	{
		switch (StatType)
		{
		case ECoreStats::STR:
			return Strength;
			
		case ECoreStats::MAG:
			return Magic;
			
		case ECoreStats::END:
			return Endurance;
			
		case ECoreStats::AGI:
			return Agility;
			
		case ECoreStats::LUK:
			return Luck;
			
		default:
			return 0;
		}
	}
}; 