#include "System/Battle/BattleEntity.h"

ABattleEntity::ABattleEntity()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABattleEntity::BeginPlay()
{
	Super::BeginPlay();
}