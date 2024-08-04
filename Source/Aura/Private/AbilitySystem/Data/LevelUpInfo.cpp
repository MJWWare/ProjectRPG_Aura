// Copyright MJWWare


#include "AbilitySystem/Data/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXP(int32 XP)
{
	int32 Level = 1;
	bool bSearching = true;
	while(bSearching)
	{
		// LevelUpInformation[0] ignored, LevelUpInformation[1] = Level 1 info
		// LevelUpInformation[2] = Level 2 info, etc.
		if(LevelUpInformation.Num() - 1 <= Level) return Level;

		if(XP >= LevelUpInformation[Level].LevelUpRequirement)
		{
			++Level;
		}
		else
		{
			bSearching = false;
		}
	}
	return Level;
}
