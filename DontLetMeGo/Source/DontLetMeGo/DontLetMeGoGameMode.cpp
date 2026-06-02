// Copyright Epic Games, Inc. All Rights Reserved.

#include "DontLetMeGoGameMode.h"
#include "DontLetMeGoCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADontLetMeGoGameMode::ADontLetMeGoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
