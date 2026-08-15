#pragma once

#include "CoreMinimal.h"

#include "BattleEntity.generated.h"

UCLASS()
class P3R_CLONE_API ABattleEntity : public AActor
{
	GENERATED_BODY()

public:
	ABattleEntity();

protected:
	virtual void BeginPlay() override;

public:
	
};
