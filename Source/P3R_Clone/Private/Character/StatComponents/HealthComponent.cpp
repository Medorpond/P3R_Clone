#include "Character/StatComponents/HealthComponent.h"


UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// 에디터 초기값을 클램핑 후 재적용
	// 클램핑 결과에 따라 실행할 로직 (Setter 내부)의 명시적 호출
	SetMaxHealth(ClampMaxHealth(MaxHealth));
	SetHealth(ClampHealth(Health));
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
	// TODO: 최대 채력 증가 시 현재 체력 관리 Policy 구현을 고려하라.
	
	OnMaxHealthChanged.Broadcast(NewMaxHealth);
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


