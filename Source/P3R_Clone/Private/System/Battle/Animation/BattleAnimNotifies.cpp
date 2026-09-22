#include "System/Battle/Animation/BattleAnimNotifies.h"

#include "System/Battle/Interface/BattleAnimInterface.h"

UAttackHitNotify::UAttackHitNotify()
{
	
}

void UAttackHitNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                              const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	if (!IsValid(MeshComp))
	{
		UE_LOG(LogTemp, Error, TEXT("[Notify] Invalid Mesh Component"))
		return;
	}
	
	AActor* Owner = MeshComp -> GetOwner();
	
	if (auto* NotifyReceiver = Cast<IBattleAnimInterface>(Owner))
	{
		NotifyReceiver->OnAttackHit(DamageRatio);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[Notify] No Receiver Found (Cast failed)"))
	}
}
