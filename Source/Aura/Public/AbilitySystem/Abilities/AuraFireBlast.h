// Copyright MJWWare

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"
#include "AuraFireBlast.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraFireBlast : public UAuraDamageGameplayAbility
{
	GENERATED_BODY()
	
public:
	virtual FString GetAbilityDesc(int32 Level) override;
	virtual FString GetNextLevelDesc(int32 Level) override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "FireBlast")
	int32 NumFireBalls = 12;
};
