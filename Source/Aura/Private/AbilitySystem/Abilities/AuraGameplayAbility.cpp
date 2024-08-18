// Copyright MJWWare


#include "AbilitySystem/Abilities/AuraGameplayAbility.h"

FString UAuraGameplayAbility::GetDesc(int32 Level)
{
	return FString::Printf(TEXT("<Default>%s, </><Level>%d</>"), L"Default Ability Name - blah blah blah blah blah blah blah blah blah blah ", Level);
}

FString UAuraGameplayAbility::GetNextLevelDesc(int32 Level)
{
	return FString::Printf(TEXT("<Default>Next Level: </><Level>%d</> \n\t<Default>Causes more dmg </>"), Level);
}

FString UAuraGameplayAbility::GetLockedDesc(int32 Level)
{
	return FString::Printf(TEXT("<Default>Spell Locked Until Level: </><Level>%d</>"), Level);
}
