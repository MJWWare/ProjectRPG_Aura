// Copyright MJWWare


#include "AbilitySystem/Abilities/AuraFireBolt.h"

#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Actor/AuraProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
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
	const int32 MaxNum = FMath::Min(MaxNumProjectiles, GetAbilityLevel());

	//TArray<FVector> Directions = UAuraAbilitySystemLibrary::EvenlyRotatedVectors(Forward, FVector::UpVector, ProjectileSpread, NumProjectiles);
	TArray<FRotator> Rotators = UAuraAbilitySystemLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, ProjectileSpread, MaxNum);
	
	/*for(FVector& Direction : Directions)
	{
		UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation, 
	SocketLocation + Direction * 75.f, 5, FLinearColor::Red, 120, 1);
	}*/
	
	for(const FRotator& R : Rotators)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(R.Quaternion());
	
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass, SpawnTransform, GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		
		// adds damage effect spec handle here
		Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();

		// homing projectiles?
		if(bLaunchHomingProjectiles)
		{
			if(HomingTarget && HomingTarget->Implements<UCombatInterface>())
			{
				Projectile->ProjectileMovement->HomingTargetComponent = HomingTarget->GetRootComponent();
			}
			else
			{
				Projectile->HomingTargetSceneComponent = NewObject<USceneComponent>(USceneComponent::StaticClass());
				Projectile->HomingTargetSceneComponent->SetWorldLocation(ProjectileTargetLocation);
				Projectile->ProjectileMovement->HomingTargetComponent = Projectile->HomingTargetSceneComponent;			
			}
			Projectile->ProjectileMovement->HomingAccelerationMagnitude = FMath::FRandRange(HomingAccelerationMin, HomingAccelerationMax);
			Projectile->ProjectileMovement->bIsHomingProjectile = bLaunchHomingProjectiles;			
		}

		Projectile->FinishSpawning(SpawnTransform);
		
		//UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation + FVector(0,0,10), 
				//SocketLocation + FVector(0,0,10) + R.Vector() * 75.f, 5, FLinearColor::Blue, 120, 1);
	}

}
