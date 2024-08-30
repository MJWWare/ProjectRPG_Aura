// Copyright MJWWare


#include "AbilitySystem/Abilities/AuraFireBolt.h"

#include "Kismet/KismetSystemLibrary.h"


FString UAuraFireBolt::GetAbilityDesc(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	if(Level == 1)
	{
		return FString::Printf(TEXT(
				// Title
				"<Title>FIRE BOLT</>\n\n"

				// Level
				"<Small>Level: </><Level>%d</>\n"
				// ManaCost
				"<Small>Mana Cost: </><ManaCost>%.1f</>\n"
				// Cooldown
				"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
				
				"<Default>Launches a bolt of fire, exploding on impact and dealing: </>"
				// Damage
				"<Damage>%d</><Default> fire damage with a chance to burn</>"
				), Level, ManaCost, Cooldown, ScaledDamage);
	}
	else
	{
		return FString::Printf(TEXT(
				// Title
				"<Title>FIRE BOLT</>\n\n"

				// Level
				"<Small>Level: </><Level>%d</>\n"
				// ManaCost
				"<Small>Mana Cost: </><ManaCost>%.1f</>\n"
				// Cooldown
				"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

				// Number of FireBolts
				"<Default>Launches %d bolts of fire, exploding on impact and dealing: </>"
				// Damage
				"<Damage>%d</><Default> fire damage with a chance to burn</>"
				), Level, ManaCost, Cooldown, FMath::Min(Level, NumProjectiles), ScaledDamage);
	}
}

FString UAuraFireBolt::GetNextLevelDesc(int32 Level)
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

				// Number of FireBolts
				"<Default>Launches %d bolts of fire, exploding on impact and dealing: </>"
				// Damage
				"<Damage>%d</><Default> fire damage with a chance to burn</>"
				), Level, ManaCost, Cooldown, FMath::Min(Level, NumProjectiles), ScaledDamage);
}

void UAuraFireBolt::SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag,
	bool bOverridePitch, float PitchOverride, AActor* HomingTarget)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if(!bIsServer) return;

	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo(), SocketTag);
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
	if(bOverridePitch) Rotation.Pitch = PitchOverride;

	const FVector Forward = Rotation.Vector();
	const FVector LeftOfSpread = Forward.RotateAngleAxis(-ProjectileSpread / 2.f, FVector::UpVector);
	const FVector RightOfSpread = Forward.RotateAngleAxis(ProjectileSpread / 2.f, FVector::UpVector);
	
	//NumProjectiles = FMath::Min(MaxNumProjectiles, GetAbilityLevel());
	if(NumProjectiles > 1)
	{
		const float DeltaSpread = ProjectileSpread / (NumProjectiles - 1);
		for(int32 i = 0; i < NumProjectiles; i++)
		{
			const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
			UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation + FVector(0,0,10), 
		SocketLocation + FVector(0,0,10) + Direction * 75.f, 5, FLinearColor::Red, 120, 1);
		}
	}
	else
	{
		// 1 bolt
		UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation + FVector(0,0,10), 
	SocketLocation + Forward * 75.f, 5, FLinearColor::Red, 120, 1);
	}
    			
	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation, 
	SocketLocation + Forward * 100.f, 5, FLinearColor::White, 120, 1);
	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation, 
	SocketLocation + LeftOfSpread * 100.f, 5, FLinearColor::Green, 120, 1);
	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation, 
		SocketLocation + RightOfSpread * 100.f, 5, FLinearColor::Gray, 120, 1);
}
