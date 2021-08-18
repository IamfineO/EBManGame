// Fill out your copyright notice in the Description page of Project Settings.


#include "EBMan/GamePlay/StandardGameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "EBMan/GamePlay/StandardGameStateBase.h"
#include "EBMan/GamePlay/StandardPlayerController.h"
#include "EBMan/GamePlay/StandardPlayingHUD.h"

AStandardGameModeBase::AStandardGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Actor/BP_PlayerPawn"));
	if (PlayerPawnBPClass.Succeeded())
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	GameStateClass = AStandardGameStateBase::StaticClass();
	PlayerControllerClass = AStandardPlayerController::StaticClass();
	HUDClass = AStandardPlayingHUD::StaticClass();
}
