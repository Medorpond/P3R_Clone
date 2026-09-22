#include "System/Battle/BattleActors/BattleActor.h"
#include "System/Battle/BattleManager.h"
#include "System/Battle/StatComponents/AttributeComponent.h"

ABattleActor::ABattleActor()
{
	PrimaryActorTick.bCanEverTick = false;
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SKMeshComponent"));
	//AttributeComp = CreateDefaultSubobject<UAttributeComponent>(TEXT("AttributeComponent"));
}

void ABattleActor::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void ABattleActor::InitActor(ABattleManager* InManager)
{
	check(IsValid(InManager))
	BattleManager = InManager;
}


void ABattleActor::BeginTurn()
{
	UE_LOG(LogTemp, Log, TEXT("[%s] Begin Turn"), *GetActorLabel())
}

void ABattleActor::DoSomething()
{
	UE_LOG(LogTemp, Log, TEXT("[%s] Did something"), *GetActorLabel())
	
	check(IsValid(BattleManager))
	
	
	BattleManager->HandleRequest();
}

void ABattleActor::EndTurn()
{
	// NOTE: EndTurn은 "턴 종료" 내지는 "턴 반환" 을 의미하는 것이 아니라, 명시적인 "턴 종료" 요청(매니저에 의해) 에 따라 리소스를 정리하는 생명주기이다.
	// TODO: 이름 변경
	UE_LOG(LogTemp, Log, TEXT("[%s] End Turn"), *GetActorLabel())
}

FAttackFactors ABattleActor::GetAttackFactors(FGameplayTag AttackType)
{
	float DamageFactor;
	if (AttackType.MatchesTag(NativeTags::Element_Physical)) DamageFactor = Strength;
	else if (AttackType.MatchesTag(NativeTags::Element_Magic)) DamageFactor = Magic;
	else
	{
		// TODO: Use DataAsset.Guid or other identifier
		UE_LOG(LogTemp, Error, TEXT("[ABattleActor] Unresolvable AttackType at %s"), *GetActorNameOrLabel())
		DamageFactor = 1.f;
	}
	
	auto Factors = FAttackFactors();
	
	Factors.Level = Level;
	Factors.DamageFactor = DamageFactor;
	Factors.AccuracyFactor = Agility;
	Factors.CritFactor = Luck;
	
	// Override Modifiers
	
	return Factors;
}

FDefendFactors ABattleActor::GetDefendFactors(FGameplayTag AttackType)
{
	return FDefendFactors(); // TODO: 작 성
}
