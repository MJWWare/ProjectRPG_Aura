// Copyright MJWWare

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AuraGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag StartupInputTag;

	virtual FString GetAbilityDesc(int32 Level);
	virtual FString GetNextLevelDesc(int32 Level);
	static FString GetLockedDesc(int32 Level);

protected:
	float GetManaCost(float InLevel = 1) const;
	float GetCooldown(float InLevel = 1) const;
	
};
