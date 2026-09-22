#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NiagaraSystem.h"
#include "SkillData.generated.h"

UENUM(BlueprintType)
enum class ESkillVfxScope : uint8
{
	EachTarget	UMETA(DisplayName = "Each Target", ToolTip = "Play VFX once for each target."),
	Area		UMETA(DisplayName = "Area", ToolTip = "Play VFX once for target area.")
};

USTRUCT(BlueprintType)
struct FSkillPresentation
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UNiagaraSystem> Vfx;
	
	UPROPERTY(EditDefaultsOnly)
	ESkillVfxScope VfxScope;
	
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<USoundBase> Sfx;
	
	// TODO: 연출 요구사항에 따라, 위 필드를 세분화하라. 
};

USTRUCT(BlueprintType)
struct FHitCountRange
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 Min = 1;
	
	UPROPERTY(EditDefaultsOnly)
	int32 Max = 1;
};

UCLASS()
class P3R_CLONE_API USkillData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	FName Identifier;

	UPROPERTY(EditDefaultsOnly)
	FText Name;
	UPROPERTY(EditDefaultsOnly)
	FText Description;
	
	UPROPERTY(EditDefaultsOnly)
	FSkillPresentation Presentations;
	
	UPROPERTY(EditDefaultsOnly)
	FHitCountRange HitCountRange;
	
	// TODO: 타겟 타입 (적, 아, 전체)와 타겟 종류 (단일, 광역) 설정 필드
	// TODO: 'Action' 구현, Action은 내부에 Enum으로 '적용 시점' 결정.
};
