#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BaseController.generated.h"

class UInputMappingContext;

UCLASS(Abstract)
class P3R_CLONE_API ABaseController : public APlayerController
{
	GENERATED_BODY()
	
protected: // Lifecycle Methods
	virtual void BeginPlay() override;
	
protected: // Properties
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> IMC_System;
	
};
