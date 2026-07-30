#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CombatAttributeSet.generated.h"

/**
 * Auto-Create Macro for attributes (Get, Set, Init) 
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


UCLASS()
class P3R_CLONE_API UCombatAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UCombatAttributeSet();
	
public: // Attribute Lifecycle Methods
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
protected: // Attributes

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|HP")
	FGameplayAttributeData HP;
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|HP")
	FGameplayAttributeData MaxHP;
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|HP")
	FGameplayAttributeData Damage; // Damage to take. (Buffer)
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|SP")
	FGameplayAttributeData SP;
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|SP")
	FGameplayAttributeData MaxSP;
	
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Stats")
	FGameplayAttributeData Strength; // Physical Damage
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Stats")
	FGameplayAttributeData Magic; // Magic Damage
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Stats")
	FGameplayAttributeData Endurance; // Defence
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Stats")
	FGameplayAttributeData Agility; // Accuracy, Evasion, Initiative
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Stats")
	FGameplayAttributeData Luck; // CritRate, Ailment
	
public: // Attribute Macros
	ATTRIBUTE_ACCESSORS(ThisClass, HP);
	ATTRIBUTE_ACCESSORS(ThisClass, MaxHP);
	ATTRIBUTE_ACCESSORS(ThisClass, Damage);
	ATTRIBUTE_ACCESSORS(ThisClass, SP);
	ATTRIBUTE_ACCESSORS(ThisClass, MaxSP);
	ATTRIBUTE_ACCESSORS(ThisClass, Strength);
	ATTRIBUTE_ACCESSORS(ThisClass, Magic);
	ATTRIBUTE_ACCESSORS(ThisClass, Endurance);
	ATTRIBUTE_ACCESSORS(ThisClass, Agility);
	ATTRIBUTE_ACCESSORS(ThisClass, Luck);
	
};
