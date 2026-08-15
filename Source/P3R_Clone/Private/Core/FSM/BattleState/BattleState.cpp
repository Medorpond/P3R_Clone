#include "Core/FSM/BattleStates/BattleState.h"
#include "Battle/BattleManager.h"

void UBattleState::InitState(ABattleManager* InBattleManager)
{
	if (!ensureAlwaysMsgf(IsValid(InBattleManager), TEXT("[BattleState] Invalid dependency injection"))) { return; }
	BattleManager = InBattleManager;
}
