#pragma once

#include "CoreMinimal.h"
#include "StatComponentTestMocks.generated.h"

UCLASS()
class UStatTestListener : public UObject
{
	GENERATED_BODY()
public:
	bool bWasCalled = false;
	float ReceivedValue = -1.f;
	
	UFUNCTION()
	void HandleStatChange(float NewValue)
	{
		bWasCalled = true;
		ReceivedValue = NewValue;
	}
	
	UFUNCTION()
	void HandleEventBroadcast()
	{
		bWasCalled = true;
	}
	
	void Reset()
	{
		bWasCalled = false;
		ReceivedValue = -1.f;
	}
}; 
