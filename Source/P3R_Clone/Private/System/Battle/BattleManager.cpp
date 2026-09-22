#include "System/Battle/BattleManager.h"
#include "System/Battle/BattleActors/BattleActor.h"

ABattleManager::ABattleManager()
{
	PrimaryActorTick.bCanEverTick = false;
	
}

void ABattleManager::BeginPlay()
{
	Super::BeginPlay();
}

void ABattleManager::InitTurnQueue(const TArray<ABattleActor*>& BattleActors)
{
	if (BattleActors.IsEmpty()) return;
	
	TurnQueue.Reserve(BattleActors.Num());
	
	for ( auto* BattleEntity : BattleActors)
	{
		BattleEntity->InitActor(this);
		TurnQueue.Emplace(CreateTurnEntity(BattleEntity));
	}
	
	TurnQueue.Sort(SortTurnEntityByPriority);
	
	TurnIndex = 0;
	CurrentActor = TurnQueue[0].Actor;
	
	//  TEST용
	CurrentActor->BeginTurn();
}

void ABattleManager::HandleRequest()
{
	UE_LOG(LogTemp, Log, TEXT("RequestReceived"));
	
	if (TEST_GiveOneMore)
	{
		GiveOneMore();
		UE_LOG(LogTemp, Log, TEXT("One More to %s"), *CurrentActor->GetActorLabel());
	}
	else
	{
		AdvanceTurn();
	}
}

///

// void ABattleManager::Test_HandleAttackRequest()
// {
// 	// 입력에서 '공격' 요청이 들어온 경우. '스킬' 의 경우는 별도로 분리할까? 아니면 하나로 통합? 
// 	// [중요]일단 '스킬' 과 '일반 공격' 은 완전히 분리된 파이프라인을 타도록 하자. 
// 	// 나중에는 선택된 스킬에 기반해서 이 정보를 조립하도록 구성해야 할 듯. 
// 	
// 	// TODO: 여기서부터. Actor에게 AttackInfo와 DefenderInfo 받을 수 있는 API 뚫어주고, 해당 API를 호출해서 값을 처리하는 흐름을 작성.
// 		
// 	auto ContextBase = FAttackEvalContext();
// 	
// 	ContextBase.AttackType = NativeTags::Element_Magic_Fire; // TODO: 실제 공격자/스킬의 공격 속성을 가져온다. 
// 	ContextBase.Damage = 10.f; // TODO: 실제 공격자의 최종 공격력을 가져온다. 
// 	ContextBase.CritChance = 0.25f; // TODO: 실제 공격자의 최종 치명타 확률을 가져온다.
// 	ContextBase.Accuracy = 0.8f; // TODO: 실제 공격자의 명중률을 가져온다.
// 	
// 	// TODO: 새로 구상한 페르소나의 공식에 기반해서 다시 설계. 
// 	// TODO: 새로 구상한 페르소나의 공식에 대응할 수 있는 Actor를, '컴포넌트 없이' 객체지향적으로만 설계
// 	
// 	
// 	
// }
///

void ABattleManager::HandleAttackRequest()
{
	
}

void ABattleManager::AdvanceTurn()
{
	// NOTE: Advance Turn 호출 시점에는 기존 TurnActor와 다음 TurnActor가 둘 다 프로그래밍적으로 유효해야 한다. 
	// ----> "턴 정리 함수 호출" 에서 각자가 스스로, 스스로를 파괴하든, 아니면 State: Dead 상태로 유지 (아군의 경우) 하도록...
	// ----> 스스로 판단하도록 만들어야 한다는 뜻이다. 그것이 책임 경계이며, BattleManager가 이에 대해 전부 아는 것은 오히려...
	// ----> 책임 경계가 흐려지는 설계일 수 있다. (물론, 설계에 따라 이 책임은 Manager에게 위임될 수도 있으나, 우선 이를 기본 골자로 한다.
	
	if (IsValid(CurrentActor))
	{
		CurrentActor->EndTurn();
	}
	
	// UpdateCurrentActor and revaluate
	AdvanceTurnQueue();
	
	if (IsValid(CurrentActor))
	{
		FTimerDelegate Delegate;
		Delegate.BindUObject(CurrentActor, &ABattleActor::BeginTurn);
		
		GetWorld()->GetTimerManager().SetTimerForNextTick(Delegate);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[BattleManager] NextActor is invalid after turn advance"))		
	}
}

void ABattleManager::GiveOneMore()
{
	// TODO: 나중에 AdvanceTurn이랑 어째 잘 정리해보자.
	UE_LOG(LogTemp, Log, TEXT("OneMore Given"));
	
	if (IsValid(CurrentActor))
	{
		CurrentActor->EndTurn();
		
		FTimerDelegate Delegate;
		Delegate.BindUObject(CurrentActor, &ABattleActor::BeginTurn);
		
		GetWorld()->GetTimerManager().SetTimerForNextTick(Delegate);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[BattleManager] CurrentActor is invalid while OneMore Occurred"))		
	}
	
}

void ABattleManager::AdvanceTurnQueue()
{
	// NOTE: 책임. 턴 Index를 한 칸 이동하고, CurrentActor를 이에 맞도록 업데이트한다.
	// TODO: 내부적으로 Invalid한 Actor를 점검하여 Skip하는 로직 구성 (etc. Dead)
	// TODO: 최종 결정된 Actor는: A. Valid함이 보장되도록 게임 시스템 구성.(check만) B. Validation 후 bool형 결과 반환. 
	
	TurnIndex = CalcNextTurnIndex();
	
	if (!TurnQueue.IsValidIndex(TurnIndex))
	{
		CurrentActor = nullptr; 
		return;
	}

	CurrentActor = TurnQueue[TurnIndex].Actor;
}

FTurnEntry ABattleManager::CreateTurnEntity(ABattleActor* InActor)
{
	FTurnEntry TurnEntity = FTurnEntry();
	
	if (IsValid(InActor))
	{
		TurnEntity.Actor = InActor;
		TurnEntity.TurnPriority = InActor->GetSpeed();
	} 
	
	return TurnEntity;
}
