#include "Core/FSM/BaseState.h"
#include "Core/FSM/StateMachine.h"

void UBaseState::SetOwningFSM(UStateMachine* InFSM)
{
	checkf(IsValid(InFSM), TEXT("Invalid FSM injection at %s"), *GetName());
	OwningFSM = InFSM;
}

void UBaseState::Enter()
{
	NativeEnter();
	ReceiveEnter();
}

void UBaseState::Update(float DeltaTime)
{
	NativeUpdate(DeltaTime);
	ReceiveUpdate(DeltaTime);
}

void UBaseState::Exit()
{
	NativeExit();
	ReceiveExit();
}
