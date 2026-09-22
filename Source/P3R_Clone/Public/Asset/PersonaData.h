#pragma once

#include "CoreMinimal.h"
#include "Core/Types.h"
#include "Engine/DataAsset.h"
#include "PersonaData.generated.h"



USTRUCT(BlueprintType)
struct FPersonaAnimSet
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UAnimMontage> Idle;
	
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UAnimMontage> CastPhysical;
	
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UAnimMontage> CastMagic;
	
};

UCLASS()
class P3R_CLONE_API UPersonaData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
	// TODO: 영역별로 Bundle 지정
	
	UPROPERTY(EditDefaultsOnly)
	FName Identifier;
	
	UPROPERTY(EditDefaultsOnly)
	FText Name;
	UPROPERTY(EditDefaultsOnly)
	FText Description;
		
	UPROPERTY(EditDefaultsOnly)
	FCoreStats CoreStats;
	
	// TODO: 스킬 리스트 (Soft 참조로, 스킬 클래스 결정된 이후에. )
	
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<USkeletalMesh> Mesh_Basic;
	
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<USkeletalMesh> Mesh_Summoned;
	
	// TODO: 데이터 테이블을 통해 베이킹하거나, DT 자체 사용을 것을 고려하라.
	UPROPERTY(EditDefaultsOnly)
	FPersonaAnimSet Animations;
	
	// TODO: 나중에 필요한 데이터가 있으면 추가로 넣어라...! 우선은 여기까지. 
};
