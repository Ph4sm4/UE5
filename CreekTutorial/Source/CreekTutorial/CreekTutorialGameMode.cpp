// Copyright Epic Games, Inc. All Rights Reserved.

#include "CreekTutorialGameMode.h"
#include "CreekTutorialCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACreekTutorialGameMode::ACreekTutorialGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
