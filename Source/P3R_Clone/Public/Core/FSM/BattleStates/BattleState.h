#pragma once

#include "CoreMinimal.h"
#include "Core/FSM/BaseState.h"
#include "BattleState.generated.h"

class ABattleManager;

/**
 * @brief Mediator state for BattleManager (Battle state)
 * @note You can derive a blueprint right from mediator, if you don't need any native implementation
 */
UCLASS(Abstract, Blueprintable)
class P3R_CLONE_API UBattleState : public UBaseState
{
	GENERATED_BODY()
	
public:
	virtual void InitState(ABattleManager* InBattleManager);
	ABattleManager* GetBattleManager() const { return BattleManager; }
	
private:
	UPROPERTY()
	TObjectPtr<ABattleManager> BattleManager;
};
