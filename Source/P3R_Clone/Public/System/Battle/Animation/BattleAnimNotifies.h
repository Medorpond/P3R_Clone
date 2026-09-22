#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "BattleAnimNotifies.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Attack Hit Notify"))
class P3R_CLONE_API UAttackHitNotify : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAttackHitNotify();
	
public:
	virtual void Notify(
		USkeletalMeshComponent* MeshComp,
		UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference
		) override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, 
		meta = (ClampMin = "0.0", UIMin = "0.0",
				ClampMax = "1.0", UIMax = "1.0",
				AllowPrivateAccess = "true"))
	float DamageRatio = 1.f;
};
