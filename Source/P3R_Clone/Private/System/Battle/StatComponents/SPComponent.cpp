#include "System/Battle/StatComponents/SPComponent.h"

USPComponent::USPComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USPComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// 에디터 설정값에 Policy 적용 보장
	// 반드시 Max를 먼저 설정해야 함
	SetMaxSP(MaxSP);
	SetSP(SP);
}

void USPComponent::SetSP(float InSP)
{
	const float NewSP = ClampSP(InSP);
	SP = NewSP;
	
	// TODO: Add Business Logic Implementation
	
	OnSPChanged.Broadcast(NewSP);
}

void USPComponent::SetMaxSP(float InMaxSP)
{
	const float NewMaxSP = ClampMaxSP(InMaxSP);
	MaxSP = NewMaxSP;
	
	// TODO: Add Business Logic Implementation
	
	if (MaxSP < SP)
	{
		SetSP(MaxSP);
	}
	// TODO: 최대값 증가 시 현재값 관리 Policy 구현을 고려하라.
	
	OnMaxSPChanged.Broadcast(NewMaxSP);
}