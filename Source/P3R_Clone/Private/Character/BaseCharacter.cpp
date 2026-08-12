#include "P3R_Clone/Public/Character/BaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "GAS/CombatAttributeSet.h"
#include "P3R_Logs.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
	//AbilitySystem->SetIsReplicated(true);
	
	CreateDefaultSubobject<UCombatAttributeSet>(TEXT("CombatAttributeSet"));
	
	// Set default values under
}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (AbilitySystem)
	{
		AbilitySystem->InitAbilityActorInfo(this, this);
	}
	else
	{
		UE_LOG(GAS, Error, TEXT("Invalid Ability System on %s"), *GetName())
	}
}
