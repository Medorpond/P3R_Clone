#include "Core/FSM/StateMachine.h"

#include "P3R_Logs.h"
#include "Core/FSM/BaseState.h"


void UStateMachine::InitMachine(TArray<UBaseState*>&& InStates, FGameplayTag InitialStateTag)
{
	// 빈 상태 묶음 주입. (FSM 초기화 불가)
	checkf(!InStates.IsEmpty(), TEXT("[StateMachine] Empty states delivered to %s"), *GetName());
	
	for (UBaseState* State : InStates)
	{
		RegisterState(State);
	}
	
	if (!ensureMsgf(InitialStateTag.IsValid(), TEXT("[StateMachine] Initial state not set at %s"), *GetName()))
	{
		InitialStateTag = InStates[0]->GetStateTag();
	}
	
	EnterInitialState(InitialStateTag);
}

void UStateMachine::ChangeState(const FGameplayTag& NextStateTag)
{
	UBaseState* NextState = StateMap.FindRef(NextStateTag);
	
	// 다음 상태가 유효하지 않을 경우 이전 상태 유지
	if (UNLIKELY(!IsValid(NextState)))
	{
		UE_LOG(
			FSM,
			Error,
			TEXT("[StateMachine] Invalid next state with tag: %s at %s"),
			*NextStateTag.ToString(), *GetName()
		);
		
		// 이전 상태 또한 유효하지 않을 경우, 크래시 (복구 불가한 치명적 오류)
		checkf(
			IsValid(CurrentState),
			TEXT("[StateMachine] Cannot fallback to CurrentState at %s (Invalid CurrentState)"),
			*GetName()
		);
		
		return;
	}
	
	if (ensureAlwaysMsgf(IsValid(CurrentState), TEXT("[StateMachine] Invalid current state before Exit call")))
	{
		CurrentState->Exit();
	}
	
	CurrentState = NextState;
	CurrentState->Enter();
}

void UStateMachine::Update(float DeltaTime)
{
	if (!ensureMsgf(
		IsValid(CurrentState),
		TEXT("[StateMachine] Update attempted with invalid state at %s"),
		*GetName()))
	{ return; }
	
	CurrentState->Update(DeltaTime);
}

void UStateMachine::RegisterState(UBaseState* InState)
{
	// A state instance cannot be null. Check if FSM Owner is injecting nullptr while initializing states or not. 
	checkf(IsValid(InState), TEXT("[StateMachine]: Invalid state registration attempt at %s"), *GetName());
	
	// State tag must not be duplicated
	if (!ensureAlwaysMsgf(
		!StateMap.Contains(InState->GetStateTag()),
		TEXT("[StateMachine] Duplicated register request with tag: %s at %s"), 
		*InState->GetStateTag().ToString(), *GetName())
	){ return; }
	
	InState->SetOwningFSM(this);
	StateMap.Emplace(InState->GetStateTag(), InState);
}

void UStateMachine::EnterInitialState(const FGameplayTag& InitialStateTag)
{
	CurrentState = StateMap.FindRef(InitialStateTag);
	
	// 유효하지 않은 초기 상태 (상태 진입 불가)
	checkf(
		IsValid(CurrentState),
		TEXT("[StateMachine] Invalid Initial State with tag: %s at %s"),
		*InitialStateTag.ToString(), *GetName()
	);
	
	CurrentState->Enter();
}
