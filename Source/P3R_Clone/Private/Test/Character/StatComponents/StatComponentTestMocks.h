#pragma once

#include "CoreMinimal.h"
#include "StatComponentTestMocks.generated.h"

UCLASS()
class UHealthTestListener : public UObject
{
	GENERATED_BODY()
public:
	bool bWasCalled = false;
	float ReceivedValue = -1.f;
	
	UFUNCTION()
	void HandleHealthChanged(float NewValue)
	{
		bWasCalled = true;
		ReceivedValue = NewValue;
	}
	
	UFUNCTION()
	void HandleHealthDeplete()
	{
		bWasCalled = true;
	}
	
	void Reset()
	{
		bWasCalled = false;
		ReceivedValue = -1.f;
	}
}; 
