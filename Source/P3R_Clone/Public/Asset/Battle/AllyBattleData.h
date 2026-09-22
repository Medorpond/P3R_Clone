#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AllyBattleData.generated.h"



UCLASS(BlueprintType)
class P3R_CLONE_API UAllyBattleData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	FName Identifier;
	
	UPROPERTY(EditDefaultsOnly)
	FText Name;

	
	
};
