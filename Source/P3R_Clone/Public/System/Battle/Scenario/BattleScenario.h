#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BattleScenario.generated.h"

/**
 * 
 */
UCLASS()
class P3R_CLONE_API UBattleScenario : public UObject
{
	GENERATED_BODY()
	
public:
	void PlayScenario();
};
