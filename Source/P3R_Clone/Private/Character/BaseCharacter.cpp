#include "P3R_Clone/Public/Character/BaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "P3R_Logs.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}