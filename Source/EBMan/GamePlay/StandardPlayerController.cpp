// Fill out your copyright notice in the Description page of Project Settings.


#include "EBMan/GamePlay/StandardPlayerController.h"

AStandardPlayerController::AStandardPlayerController()
{
}

APlayerPawn* AStandardPlayerController::GetPlayerPawn()
{
	return Cast<APlayerPawn>(GetPawn());
}

class AStandardPlayingHUD* AStandardPlayerController::GetStandardHUD()
{
	return Cast<AStandardPlayingHUD>(MyHUD);
}

void AStandardPlayerController::BeginRound()
{
	if (GetPlayerPawn())
	{
		GetStandardHUD()->BeginRound();
		GetPlayerPawn()->ChangeRunningState(ERoundState::Preparing);
		bShowMouseCursor = false;
	}
	else
	{
		if (GetWorld())
		{
			TWeakObjectPtr<AStandardPlayerController> Weak_This(this);
			GetWorld()->GetTimerManager().SetTimerForNextTick([Weak_This]()
			{
				if (Weak_This.IsValid())
				{
					Weak_This->BeginRound();
				}
			});
		}
	}
}
