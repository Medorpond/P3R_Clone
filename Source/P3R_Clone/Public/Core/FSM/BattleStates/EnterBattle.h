// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleState.h"
#include "EnterBattle.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class P3R_CLONE_API UEnterBattle final : public UBattleState 
{
	GENERATED_BODY()
	
public:
	virtual void InitState(ABattleManager* InBattleManager) override;
	
protected:
	virtual void NativeEnter() override;
	virtual void NativeExit() override;
	virtual void NativeUpdate(float DeltaTime) override;
};
