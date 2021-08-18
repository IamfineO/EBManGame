// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EBMan/Pawn/PlayerPawn.h"
#include "EBMan/GamePlay/StandardPlayingHUD.h"
#include "StandardPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class EBMAN_API AStandardPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AStandardPlayerController();

	class APlayerPawn* GetPlayerPawn();

	class AStandardPlayingHUD* GetStandardHUD();

	void BeginRound();
};
