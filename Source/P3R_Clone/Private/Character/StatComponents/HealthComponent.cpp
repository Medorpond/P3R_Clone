#include "Character/StatComponents/HealthComponent.h"


UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// 에디터 설정값에 Policy 적용 보장
	// 반드시 Max를 먼저 설정해야 함
	SetMaxHealth(MaxHealth);
	SetHealth(Health);
}

void UHealthComponent::SetHealth(float InHealth)
{
	const float NewHealth = ClampHealth(InHealth);
	Health = NewHealth;
	
	// TODO: Add Business Logic Implementation
	
	OnHealthChanged.Broadcast(NewHealth);
	
	if (NewHealth <= 0.f)
	{
		OnHealthDepleted.Broadcast();
	}
}

void UHealthComponent::SetMaxHealth(float InMaxHealth)
{
	const float NewMaxHealth = ClampMaxHealth(InMaxHealth);
	MaxHealth = NewMaxHealth;
	
	// TODO: Add Business Logic Implementation
	
	if (MaxHealth < Health)
	{
		SetHealth(MaxHealth);
	}
	// TODO: 최대값 증가 시 현재값 관리 Policy 구현을 고려하라.
	
	OnMaxHealthChanged.Broadcast(NewMaxHealth);
}