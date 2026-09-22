#pragma once

#include "CoreMinimal.h"
#include "BattleTypes.h"

#include "BattleManager.generated.h"

class ABattleActor;

USTRUCT()
struct FTurnEntry
{
	GENERATED_BODY()
	
	UPROPERTY()
	TObjectPtr<ABattleActor> Actor = nullptr;
	
	UPROPERTY()
	float TurnPriority = 0.f; 
	
	FTurnEntry(){}
	explicit FTurnEntry(ABattleActor* InActor, float Priority) : Actor(InActor), TurnPriority(Priority) {}
};

UCLASS()
class P3R_CLONE_API ABattleManager : public AActor
{
	GENERATED_BODY()

public:
	ABattleManager();
	
protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void InitTurnQueue(const TArray<ABattleActor*>& BattleActors);
	// InsertToTurnQueue
	// protected: RemoveFromTurnQueue
	
	void HandleRequest();
	
	UFUNCTION(BlueprintCallable) // TODO: 테스트 완료 후 본 함수로 변경
	void HandleAttackRequest();
	
	UPROPERTY(EditAnywhere)
	bool TEST_GiveOneMore = false;
	
protected:
	void AdvanceTurn();
	void GiveOneMore();
	void AdvanceTurnQueue();
	
	int32 CalcNextTurnIndex() const
	{
		/* TODO: 함수의 사용 방식 등을 고려하여, 나중에 엣지케이스에 대한 대응 코드를 작성하라.
		 * 현재는 Invalid한 경우 -1을 반환하도록. (TurnQueue가 비었을 경우) 
		 */
		return TurnQueue.Num() > 0 ? (TurnIndex + 1) % TurnQueue.Num() : -1;
	}
	
	

private:
	UPROPERTY(VisibleAnywhere, Category = "TurnSystem")
	TArray<FTurnEntry> TurnQueue;
	
	UPROPERTY()
	int32 TurnIndex = 0;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ABattleActor> CurrentActor; // TODO: 턴 시스템의 결과값으로 대체
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ABattleActor> TargetActor; // TODO: 타게팅 시스템의 결과값으로 대체
	
	
	FTurnEntry CreateTurnEntity(ABattleActor* InActor);
	static bool SortTurnEntityByPriority(const FTurnEntry& A, const FTurnEntry& B)
	{
		return A.TurnPriority > B.TurnPriority;
	}
};