// Copyright MJWWare


#include "AbilitySystem/Abilities/AuraFireBlast.h"

FString UAuraFireBlast::GetAbilityDesc(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	
		return FString::Printf(TEXT(
				// Title
				"<Title>FIRE BLAST</>\n\n"

				// Level
				"<Small>Level: </><Level>%d</>\n"
				// ManaCost
				"<Small>Mana Cost: </><ManaCost>%.1f</>\n"
				// Cooldown
				"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
				
				"<Default>Launches %d fireballs in all directions, each coming back and exploding, causing </>"
				// Damage
				"<Damage>%d</><Default> radial fire damage with a chance to burn</>"
				), Level, ManaCost, Cooldown, NumFireBalls, ScaledDamage);
	
}

FString UAuraFireBlast::GetNextLevelDesc(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	
	return FString::Printf(TEXT(
			// Title
			"<Title>NEXT LEVEL</>\n\n"

			// Level
			"<Small>Level: </><Level>%d</>\n"
			// ManaCost
			"<Small>Mana Cost: </><ManaCost>%.1f</>\n"
			// Cooldown
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
				
			"<Default>Launches %d fireballs in all directions, each coming back and exploding, causing </>"
			// Damage
			"<Damage>%d</><Default> radial fire damage with a chance to burn</>"
			), Level, ManaCost, Cooldown, NumFireBalls, ScaledDamage);
	
}
