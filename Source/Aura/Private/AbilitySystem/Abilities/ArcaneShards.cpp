// Copyright MJWWare


#include "AbilitySystem/Abilities/ArcaneShards.h"

FString UArcaneShards::GetAbilityDesc(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	if(Level == 1)
	{
		return FString::Printf(TEXT(
				// Title
				"<Title>ARCANE SHARDS</>\n\n"

				// Level
				"<Small>Level: </><Level>%d</>\n"
				// ManaCost
				"<Small>Mana Cost: </><ManaCost>%.1f</>\n"
				// Cooldown
				"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
				
				"<Default>Summon a shard of arcane energy causing arcane radial damage of </>"
				// Damage
				"<Damage>%d</><Default> at the shard origin and causing knockback</>"
				), Level, ManaCost, Cooldown, ScaledDamage);
	}
	else
	{
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
				"<Default>Summon %d shards of arcane energy causing arcane radial damage of </>"
				// Damage
				"<Damage>%d</><Default> at the shard origins and causing knockback</>"
				), Level, ManaCost, Cooldown, FMath::Min(Level, MaxNumShards), ScaledDamage);
	}
}

FString UArcaneShards::GetNextLevelDesc(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	return FString::Printf(TEXT(
			// Title
			"<Title>ARCANE SHARDS</>\n\n"

			// Level
			"<Small>Level: </><Level>%d</>\n"
			// ManaCost
			"<Small>Mana Cost: </><ManaCost>%.1f</>\n"
			// Cooldown
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			// Number of Shock Targets
			"<Default>Summon %d shards of arcane energy causing arcane radial damage of </>"
			// Damage
			"<Damage>%d</><Default> at the shard origins and causing knockback</>"
			), Level, ManaCost, Cooldown, FMath::Min(Level, MaxNumShards), ScaledDamage);
}
