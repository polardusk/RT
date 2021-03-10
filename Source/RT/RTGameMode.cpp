// Copyright Epic Games, Inc. All Rights Reserved.

#include "RTGameMode.h"
#include "RTCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARTGameMode::ARTGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
