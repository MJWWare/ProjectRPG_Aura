// Copyright MJWWare


#include "AbilitySystem/Abilities/Electrocute.h"

FString UElectrocute::GetAbilityDesc(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	if(Level == 1)
	{
		return FString::Printf(TEXT(
				// Title
				"<Title>ELECTROCUTE</>\n\n"

				// Level
				"<Small>Level: </><Level>%d</>\n"
				// ManaCost
				"<Small>Mana Cost: </><ManaCost>%.1f</>\n"
				// Cooldown
				"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
				
				"<Default>Casts a beam of lightning that attaches to the target and causes continuously </>"
				// Damage
				"<Damage>%d</><Default> lightning damage with a chance to stun</>"
				), Level, ManaCost, Cooldown, ScaledDamage);
	}
	else
	{
		return FString::Printf(TEXT(
				// Title
				"<Title>ELECTROCUTE</>\n\n"

				// Level
				"<Small>Level: </><Level>%d</>\n"
				// ManaCost
				"<Small>Mana Cost: </><ManaCost>%.1f</>\n"
				// Cooldown
				"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

				// Number of Shock Targets
				"<Default>Casts a beam of lightning that attaches to the target and then chains to %d more targets and causes continuously </>"
				// Damage
				"<Damage>%d</><Default> lightning damage with a chance to stun</>"
				), Level, ManaCost, Cooldown, FMath::Min(Level, MaxNumShockTargets) - 1, ScaledDamage);
	}

}

FString UElectrocute::GetNextLevelDesc(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	return FString::Printf(TEXT(
			// Title
			"<Title>NEXT LEVEL: </>\n\n"

			// Level
			"<Small>Level: </><Level>%d</>\n"
			// ManaCost
			"<Small>Mana Cost: </><ManaCost>%.1f</>\n"
			// Cooldown
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			// Number of Shock Targets
			"<Default>Casts a beam of lightning that attaches to the target and then chains to %d more targets and causes continuously </>"
			// Damage
			"<Damage>%d</><Default> lightning damage with a chance to stun</>"
			), Level, ManaCost, Cooldown, FMath::Min(Level, MaxNumShockTargets) - 1, ScaledDamage);

}
