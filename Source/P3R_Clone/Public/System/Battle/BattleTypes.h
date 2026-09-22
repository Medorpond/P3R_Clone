#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Core/P3R_NativeTags.h"
#include "BattleTypes.generated.h"

class ABattleActor;

UENUM(BlueprintType)
enum class EAffinityType : uint8
{
	None,
	Weak,
	Strong,
	Null,
	Repel,
	Drain
};

UENUM(BlueprintType)
enum class EHitType : uint8
{
	None,
	Weak,
	Strong,
	Null,
	Repel,
	Drain,
	Miss,
	Critical
};

// TODO: 행위별로 공식에 사용할 수 있는 인자들을 패킹해서 주는 API를 제공. '행위 기준' 이다.
// TODO: 모디파이어는 공식 계산 '사후에' 연산한다. Actor는 행위 기준으로 내부에서 Modifier를 관리. 외부에서는 행위 기준으로 쿼리.
// TODO: 결국 기준은 '행위'. 그리고, 모디파이어는 별도 구조체로 묶지 않는 편이 오히려 유지보수적으로 깔끔하다.
// TODO: 9월 18일 (金) 부터 진행 -> 목표는 하나의 온전한 공격 사이클의 구성 및 검증.
// NOTE: 학교 가는 날인 만큼, 풀 개발이 안 될 수도 있고, 목표량 미달할 수도 있다. 하지만 구현에 집중하라.

struct FAttackFactors
{
	int32 Level;
	
	float DamageFactor;
	float AccuracyFactor;
	float CritFactor;
	
	// TODO: Attack Modifiers
};

struct FDefendFactors
{
	int32  Level;
	
	// TODO: '페르소나' DataAsset을 만들고, 관련 필드에서 상성 값 판단 후 넣을 수 있도록 필드 제작
	float DefendFactor;
	float EvadeFactor;
	float CritResistFactor;
	
	// TODO: Defend Modifiers
};



/// TODO: 변경
struct FAttackResult
{
	ABattleActor* Source;
	ABattleActor* Target;
	
	FGameplayTag HitResult;
	float FinalDamage;
	
};