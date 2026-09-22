#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BattleAnimInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBattleAnimInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class P3R_CLONE_API IBattleAnimInterface
{
	GENERATED_BODY()
	
public:
	// TODO: Add params if needed. Consider binding with structure if many params are required.
	/** Callback function for attack animation key hit frame notify */
	UFUNCTION(Category = "Battle|Event|Anim")
	virtual void OnAttackHit(float DamageRatio) = 0; 
	
};
