#include "Core/BaseController.h"
#include "EnhancedInputSubsystems.h"

void ABaseController::BeginPlay()
{
	Super::BeginPlay();
	
	if (auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (IMC_System)
		{
			Subsystem->AddMappingContext(IMC_System, 0);
		}
	}
}
