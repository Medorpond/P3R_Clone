#pragma once

#include "CoreMinimal.h"
#include "BaseState.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "StateMachine.generated.h"

class UBaseState;
// TODO: 필요하면 FSM 설정을 모아서 하나의 Config 구조체로 전달할 것. "State 클래스(허용할 상태 목록)는 포함되지 않음"

/**
 * @brief General Finite State Machine.
 * @note Inject state instances to operate. Each instance must know one's dependency before injection
 */
UCLASS()
class P3R_CLONE_API UStateMachine : public UObject
{
	GENERATED_BODY()
	
public:
	void InitMachine(TArray<UBaseState*>&& InStates, FGameplayTag InitialStateTag);
	void ChangeState(const FGameplayTag& NextStateTag);
	void Update(float DeltaTime);
	
protected:
	void RegisterState(UBaseState* InState);
	void EnterInitialState(const FGameplayTag& InitialStateTag);
	
private:
	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<UBaseState>> StateMap;
	
	UPROPERTY()
	TObjectPtr<UBaseState> CurrentState;
};
