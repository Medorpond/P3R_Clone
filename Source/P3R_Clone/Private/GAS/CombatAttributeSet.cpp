#include "GAS/CombatAttributeSet.h"
#include "GameplayEffectExtension.h"

UCombatAttributeSet::UCombatAttributeSet()
{
	// TODO: Change initializing value according to save system after. (Requires: Save system)
	InitMaxHP(100.f);
	InitHP(GetMaxHP());
	
	InitMaxSP(100.f);
	InitSP(GetMaxSP());
	
	InitDamage(0.f);
	
	// TODO: Attribute under must be override with stat of current persona equipped
	InitStrength(30.f);
	InitMagic(30.f);
	InitEndurance(30.f);
	InitAgility(30.f);
	InitLuck(30.f);
}

void UCombatAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetHPAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHP());
	}
	else if (Attribute == GetSPAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxSP());
	}
	else if (Attribute == GetMaxHPAttribute())
	{
		NewValue = FMath::Max(NewValue, 1.f);
	}
	else if (Attribute == GetMaxSPAttribute())
	{
		NewValue = FMath::Max(NewValue, 1.f);
	}
	else
	{
		return; // Do not clamp and ignore.
	}
}

void UCombatAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		const float DamageToApply = GetDamage();
		SetDamage(0.f);
		
		if (DamageToApply > 0.f)
		{
			const float NewHP = FMath::Clamp(GetHP() - DamageToApply, 0.f, GetMaxHP());
			SetHP(NewHP);
		
			// Extract context data
			FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
			AActor* Instigator = Context.GetInstigator();
			AActor* Avatar = GetOwningActor();
			
			if (GetHP() <= 0.f)
			{
				// TODO: On death event (Requires: BattleManager, BroadcastSystem)
			}
			else
			{
				// TODO: On hit event (Requires: BattleManager, BroadcastSystem)
			}
		}
	}
}

