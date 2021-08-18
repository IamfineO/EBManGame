// Fill out your copyright notice in the Description page of Project Settings.


#include "EBMan/GamePlay/StandardGameStateBase.h"
#include "EBMan/GamePlay/StandardPlayerController.h"
#include "EBMan/Pawn/PlayerPawn.h"
#include "EBMan/GamePlay/RoundStateMacheine.h"
#include "Kismet/GameplayStatics.h"

AStandardGameStateBase::AStandardGameStateBase()
{
	PrimaryActorTick.bCanEverTick = true;

	CurrentRoundState = ERoundState::Unknown;
	CurrentRoundIndex = EGameRound::Max;
	PendingRoundIndex = EGameRound::Max;
	CurrentLevelName = NAME_None;
	PendingLevelName = NAME_None;

	PrepareTime = 3.f;

	FSM = CreateDefaultSubobject<URoundStateMacheine>(TEXT("FSM"));
	FSM->InitStateMachine(this);

	InitLevelName();
}

void AStandardGameStateBase::BeginPlay()
{
	//BeginRound();
}

void AStandardGameStateBase::Tick(float DeltaSeconds)
{
	if (FSM)
	{
		FSM->UpdateState(DeltaSeconds);
	}
}

void AStandardGameStateBase::BeginRound() {
	if (CoinManager)
	{
		PrepareTime = 3.f;
		CoinManager->SpawnCoin();
		CoinSumRemain = CoinManager->GetCoinSum();

	}
	else
	{
		if (GetWorld())
		{
			TWeakObjectPtr<AStandardGameStateBase> Weak_This(this);
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

void AStandardGameStateBase::ChangeCurrentRoundState(ERoundState NewState)
{
	if (CurrentRoundState == NewState)
	{
		return;
	}
	CurrentRoundState = NewState;
	if (FSM)
	{
		FSM->ChangeState(RoundStateFromEnum(NewState));
	}
}

class RoundState* AStandardGameStateBase::RoundStateFromEnum(ERoundState InState)
{
	switch (InState)
	{
	case ERoundState::InMenu:
		return RoundState_InMenu::Get();
	case ERoundState::Preparing:
		return RoundState_Preparing::Get();
	case ERoundState::Running:
		return RoundState_Running::Get();
	case ERoundState::Win:
		return RoundState_Win::Get();
	case ERoundState::Fail:
		return RoundState_Fail::Get();
	default:
		break;
	}
	return nullptr;
}

FName AStandardGameStateBase::LevelNameFromEnum(EGameRound InRound)
{
	switch (InRound)
	{
	case EGameRound::First:
		return LevelOneName;
	case EGameRound::Second:
		return LevelTwoName;
	case EGameRound::Third:
		return LevelThreeName;
	case EGameRound::Fourth:
		return LevelFourName;
	case EGameRound::Fifth:
		return LevelFiveName;
	default:
		break;
	}
	return NAME_None;
}

EGameRound AStandardGameStateBase::GetNextRoundIndex()
{
	if (CurrentRoundIndex < EGameRound::Max)
	{
		uint8 Temp = (uint8)CurrentRoundIndex;
		++Temp;
		return (EGameRound)Temp;
	}
	return CurrentRoundIndex;
}

void AStandardGameStateBase::ResetRound()
{
	if (CoinManager)
	{
		CoinManager->CleanRestCoins();
	}
	CoinSumRemain = 0;
	RunInfoString = FString::Printf(TEXT("ResidueCoin: %d"), CoinSumRemain);
}

void AStandardGameStateBase::OpenRound(EGameRound InRound)
{
	PendingRoundIndex = InRound;
	PendingLevelName = LevelNameFromEnum(InRound);

	UnloadRoundLevel();
}

void AStandardGameStateBase::UnloadRoundLevel()
{
	FLatentActionInfo LatentAction;
	LatentAction.ExecutionFunction = TEXT("OnUnloadLevelComplete");
	LatentAction.CallbackTarget = this;
	LatentAction.Linkage = 0;
	UGameplayStatics::UnloadStreamLevel(this, CurrentLevelName, LatentAction, true);
}

void AStandardGameStateBase::OnUnloadLevelComplete()
{
	FLatentActionInfo LatentAction;
	LatentAction.ExecutionFunction = TEXT("OnLoadLevelComplete");
	LatentAction.CallbackTarget = this;
	LatentAction.Linkage = 0;
	UGameplayStatics::LoadStreamLevel(this, PendingLevelName, true, true, LatentAction);
}

void AStandardGameStateBase::OnLoadLevelComplete()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("OnLoadLevelComplete"));

	CurrentLevelName = PendingLevelName;
	CurrentRoundIndex = PendingRoundIndex;
	PendingLevelName = NAME_None;
	PendingRoundIndex = EGameRound::Max;
	if (CurrentRoundIndex == EGameRound::InMenu)
	{
		ChangeCurrentRoundState(ERoundState::InMenu);
	}
	else if (CurrentRoundIndex == EGameRound::Max)
	{
	}
	else
	{
		ChangeCurrentRoundState(ERoundState::Preparing);
	}

}

void AStandardGameStateBase::InitLevelName()
{
	LevelOneName = TEXT("Level_One");
	LevelOneNightName = TEXT("Level_One_Night");
	LevelTwoName = TEXT("Level_Two");
	LevelTwoNightName = TEXT("Level_Two_Night");
	LevelThreeName = TEXT("Level_Three");
	LevelThreeNightName = TEXT("Level_Three_Night");
	LevelFourName = TEXT("Level_Four");
	LevelFourNightName = TEXT("Level_Four_Night");
	LevelFiveName = TEXT("Level_Five");
	LevelFiveNightName = TEXT("Level_Five_Night");

}
