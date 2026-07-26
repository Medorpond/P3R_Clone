#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "BaseCharacter.generated.h"

class UAbilitySystemComponent;

UCLASS(Abstract)
class P3R_CLONE_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystem; }
	virtual void PossessedBy(AController* NewController) override;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystem;
};
