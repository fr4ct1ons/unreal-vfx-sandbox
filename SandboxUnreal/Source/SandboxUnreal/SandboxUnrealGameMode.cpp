// Copyright Epic Games, Inc. All Rights Reserved.

#include "SandboxUnrealGameMode.h"
#include "SandboxUnrealCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASandboxUnrealGameMode::ASandboxUnrealGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
