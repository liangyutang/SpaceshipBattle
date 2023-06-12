// Copyright Epic Games, Inc. All Rights Reserved.


#include "SpaceshipBattleGameModeBase.h"

ASpaceshipBattleGameModeBase::ASpaceshipBattleGameModeBase()
{
	Score = 0;
}

void ASpaceshipBattleGameModeBase::IncreaseScore()
{
	Score++;
}
