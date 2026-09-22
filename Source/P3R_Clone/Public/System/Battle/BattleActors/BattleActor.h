#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "System/Battle/BattleTypes.h"
#include "BattleActor.generated.h"

class ABattleManager;
class UAttributeComponent;

UCLASS()
class P3R_CLONE_API ABattleActor : public AActor
{
	GENERATED_BODY()

public:
	ABattleActor();
	
protected:
	virtual void BeginPlay() override;

public:
	void InitActor(ABattleManager* InManager);
	
	// Attr APIs
	virtual float GetSpeed() const { return Agility; }

	// Turn APIs
	void BeginTurn();
	
	UFUNCTION(BlueprintCallable)
	void DoSomething();
	
	void EndTurn();
	
	
	// PreCalcFactors
	virtual FAttackFactors GetAttackFactors(FGameplayTag AttackType);
	virtual FDefendFactors GetDefendFactors(FGameplayTag AttackType);
	
protected:
	// Fields (For test, must refactor after function development)
	UPROPERTY(EditAnywhere)
	int32 Level = 1.f;
	
	// TODO: '힘마내속운' 은 함께 붙어다니므로 구조체로 하나로 묶어 관리해도 무관할지도 모른다. -> 에셋 만드는 시점에 고려하기
	UPROPERTY(EditAnywhere)
	int32 Strength = 32;
	UPROPERTY(EditAnywhere)
	int32 Magic = 28;
	UPROPERTY(EditAnywhere)
	int32 Resist = 34;
	UPROPERTY(EditAnywhere)
	int32 Agility = 20;
	UPROPERTY(EditAnywhere)
	int32 Luck = 30;
	
	
private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> MeshComp;
	
	UPROPERTY(VisibleInstanceOnly)
	TObjectPtr<ABattleManager> BattleManager;
};
