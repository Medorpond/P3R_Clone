#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BattleManager.generated.h"

class ABaseCharacter;

/**
 * Data Struct for turn management
 */
USTRUCT(BlueprintType)
struct FTurnData
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TWeakObjectPtr<ABaseCharacter> Character = nullptr;
	
	float Agility = 0.f;
	
	bool operator<(const FTurnData& Other) const
	{
		//TODO: Add sorting condition of same speed
		return Agility > Other.Agility;
	}
	
public: // Constructor
	FTurnData(){};
	explicit FTurnData(ABaseCharacter* InCharacter);
};



UCLASS()
class P3R_CLONE_API ABattleManager : public AActor
{
	GENERATED_BODY()

public:
	ABattleManager();

public:
	
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Battle|Turn")
	TArray<FTurnData> TurnQueue;
	int32 TurnIndex = 0.f;
	
	void SortTurnQueue();
	void InsertToQueue(ABaseCharacter* InCharacter);
	void RemoveFromQueue(ABaseCharacter* InCharacter);
	
	/** 
	 * @brief Move turn index forward. Wrap around if index is out of bound.
	 * @note This function advance index only, and does not process any logic regarding starting next turn.
	 */
	FORCEINLINE void AdvanceTurnIndex()
	{
		if (TurnQueue.Num() == 0)
		{
			TurnIndex = 0;
			return;
		}
		
		TurnIndex = (TurnIndex + 1) % TurnQueue.Num();
	}
	
	/** 
	 * @brief Move turn index backward. Wrap around if index is out of bound.
	 * @note This function reverse index only, and does not process any logic regarding starting next turn.
	 */
	FORCEINLINE void ReverseTurnIndex()
	{
		if (TurnQueue.Num() == 0)
		{
			TurnIndex = 0;
			return;
		}
		
		TurnIndex = (TurnIndex - 1 + TurnQueue.Num()) % TurnQueue.Num();
	}
	
};