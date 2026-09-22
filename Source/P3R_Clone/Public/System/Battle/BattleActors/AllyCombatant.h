#pragma once

#include "CoreMinimal.h"
#include "BattleActor.h"
#include "AllyCombatant.generated.h"

UCLASS()
class P3R_CLONE_API AAllyCombatant : public ABattleActor
{
	GENERATED_BODY()

public:
	AAllyCombatant();

protected:
	UPROPERTY(EditAnywhere)
	int32 DefencePoint = 132;
	UPROPERTY(EditAnywhere)
	int32 EvadePoint = 68;
	
};
