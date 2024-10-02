// Copyright MJWWare

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraBeamSpell.h"
#include "Electrocute.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UElectrocute : public UAuraBeamSpell
{
	GENERATED_BODY()
	
public:
	virtual FString GetAbilityDesc(int32 Level) override;
	virtual FString GetNextLevelDesc(int32 Level) override;
	
};
