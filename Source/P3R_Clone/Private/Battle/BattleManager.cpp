#include "Battle/BattleManager.h"
#include "AbilitySystemGlobals.h"
#include "Character/BaseCharacter.h"
#include "GAS/CombatAttributeSet.h"

FTurnData::FTurnData(ABaseCharacter* InCharacter)
{
	if (!ensureMsgf(IsValid(InCharacter), TEXT("[FTurnData] Invalid Character Input"))) { return; }
	Character = InCharacter;
	
	
	const UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(InCharacter);
	if (!ensureMsgf(ASC != nullptr, TEXT("[FTurnData] AbilitySystem not found on %s"), *InCharacter->GetName())) { return; }
	
	const auto* CombatAttrSet = ASC->GetSet<UCombatAttributeSet>();
	if (!ensureMsgf(CombatAttrSet != nullptr, TEXT("[FTurnData] Agility(CombatAttributeSet) not found on %s"), *InCharacter->GetName())) { return; }
	
	Agility = CombatAttrSet->GetAgility();
	
	// TODO: Initialize new properties here as they are added
}

ABattleManager::ABattleManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABattleManager::SortTurnQueue()
{
	TurnQueue.StableSort();
}

void ABattleManager::InsertToQueue(ABaseCharacter* InCharacter)
{
	FTurnData TurnData = FTurnData(InCharacter);
	const int32 InsertIndex = Algo::LowerBound(TurnQueue, TurnData);
	
	TurnQueue.Insert(MoveTemp(TurnData), InsertIndex);
	
	// Adjust index to match turn order
	if (InsertIndex <= TurnIndex)
	{
		AdvanceTurnIndex();
	}
}

void ABattleManager::RemoveFromQueue(ABaseCharacter* InCharacter)
{
	for (int32 i = 0; i < TurnQueue.Num(); ++i)
	{
		if (TurnQueue[i].Character == InCharacter)
		{
			TurnQueue.RemoveAt(i);
			if (i <= TurnIndex)
			{
				ReverseTurnIndex();
				if (i == TurnIndex)
				{
					// Advance Turn
					// TODO: Use FSM to prevent excessive call stack depth issue. (Requires: Refactoring)
				}
			}
			break;
		}
	}
}