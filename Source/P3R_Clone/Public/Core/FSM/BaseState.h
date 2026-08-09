#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameplayTagContainer.h"
#include "BaseState.generated.h"

class UStateMachine;

/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class P3R_CLONE_API UBaseState : public UObject
{
	GENERATED_BODY()
	
public:
	UStateMachine* GetOwningFSM() const { return OwningFSM; }
	void SetOwningFSM(UStateMachine* InFSM);
	
	const FGameplayTag& GetStateTag() const { return StateTag; }
	
	void Enter();
	void Update(float DeltaTime);
	void Exit();
	
protected:
	virtual void NativeEnter() {};
	virtual void NativeUpdate(float DeltaTime) {};
	virtual void NativeExit() {};
	
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="On State Enter"))
	void ReceiveEnter();
	
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="On State Update"))
	void ReceiveUpdate(float DeltaTime);
	
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="On State Exit"))
	void ReceiveExit();
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true", Categories="State"))
	FGameplayTag StateTag;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStateMachine> OwningFSM;
};
