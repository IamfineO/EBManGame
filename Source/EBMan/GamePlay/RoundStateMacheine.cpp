// Fill out your copyright notice in the Description page of Project Settings.


#include "EBMan/GamePlay/RoundStateMacheine.h"
#include "EBMan/EBGameType.h"
#include "EBMan/GamePlay/StandardPlayerController.h"
#include "EBMan/GamePlay/StandardGameStateBase.h"
#include "Kismet/GameplayStatics.h"

void URoundStateMacheine::InitStateMachine(class AStandardGameStateBase* Owner)
{
	OwnerActor = Owner;
}

void URoundStateMacheine::UpdateState(float DeltaTime)
{
	if (OwnerActor && CurrentState)
	{
		CurrentState->Update(OwnerActor, DeltaTime);
	}
}

void URoundStateMacheine::ChangeState(RoundState* NewState)
{
	if (OwnerActor && CurrentState)
	{
		CurrentState->LeaveState(OwnerActor);
	}
	CurrentState = NewState;
	if (ensure(CurrentState))
	{
		CurrentState->EnterState(OwnerActor);
	}
}

/****************************************************
×´Ì¬ÊµÀý
*****************************************************/

#define GET_SPC_FOR_STATE \
AStandardPlayerController *SPC = Cast<AStandardPlayerController>(UGameplayStatics::GetPlayerController(SGS, 0));\
if (!SPC)\
{\
	GEngine->AddOnScreenDebugMessage((uint64)this + 1, 10, FColor::Red, TEXT("No Player Controller!!"), true, FVector2D(1.5f, 1.5f));\
	return;\
}\

void RoundState_InMenu::EnterState(class AStandardGameStateBase* SGS)
{
	GET_SPC_FOR_STATE
	if (SPC->GetStandardHUD())
	{
		SPC->GetStandardHUD()->ReturnToMainMenu();
	}
}

void RoundState_InMenu::Update(class AStandardGameStateBase* SGS, float DeltaTime)
{

}

void RoundState_InMenu::LeaveState(class AStandardGameStateBase* SGS)
{

}

RoundState_InMenu * RoundState_InMenu::Get()
{
	static RoundState_InMenu Instance;
	return &Instance;
}

void RoundState_Preparing::EnterState(class AStandardGameStateBase* SGS)
{
	GET_SPC_FOR_STATE

	if (nullptr == SGS) { return; }

	SPC->BeginRound();
	SGS->BeginRound();
}

void RoundState_Preparing::Update(class AStandardGameStateBase* SGS, float DeltaTime)
{
	if (nullptr == SGS) { return; }

	SGS->PrepareTime -= DeltaTime;

	bool bFinished = SGS->GetCoinManager() ? SGS->GetCoinManager()->UpdateCoinPrepare(DeltaTime) : false;

	GEngine->AddOnScreenDebugMessage(-9, 2.0f, FColor::Red, FString::Printf(TEXT("PrepareTime: %f"), SGS->PrepareTime));
	GEngine->AddOnScreenDebugMessage(-10, 2.0f, FColor::Red, FString::Printf(TEXT("bFinished: %d"), (bFinished?1:0)));

	if (bFinished && SGS->PrepareTime <= 0)
	{
		SGS->ChangeCurrentRoundState(ERoundState::Running);
	}
}

void RoundState_Preparing::LeaveState(class AStandardGameStateBase* SGS)
{

}

RoundState_Preparing * RoundState_Preparing::Get()
{
	static RoundState_Preparing Instance;
	return &Instance;
}

void RoundState_Running::EnterState(class AStandardGameStateBase* SGS)
{
	GET_SPC_FOR_STATE

	if (SPC->GetPlayerPawn())
	{
		SPC->GetPlayerPawn()->ChangeRunningState(ERoundState::Running);
	}
}

void RoundState_Running::Update(class AStandardGameStateBase* SGS, float DeltaTime)
{
	GET_SPC_FOR_STATE

	if (nullptr == SGS){ return; }

	SGS->RunInfoString = FString::Printf(TEXT("ResidueCoin: %d"), SGS->CoinSumRemain);

	if (SGS->CoinSumRemain <= 0)
	{
		SGS->ChangeCurrentRoundState(ERoundState::Win);

	}

}

void RoundState_Running::LeaveState(class AStandardGameStateBase* SGS)
{

}

RoundState_Running * RoundState_Running::Get()
{
	static RoundState_Running Instance;
	return &Instance;
}

void RoundState_Win::EnterState(class AStandardGameStateBase* SGS)
{
	GET_SPC_FOR_STATE

	if (SPC->GetPlayerPawn())
	{
		SPC->GetPlayerPawn()->ChangeRunningState(ERoundState::Win);
		SPC->bShowMouseCursor = true;
	}
}

void RoundState_Win::Update(class AStandardGameStateBase* SGS, float DeltaTime)
{


}

void RoundState_Win::LeaveState(class AStandardGameStateBase* SGS)
{
	if (SGS)
	{
		SGS->ResetRound();
	}
}

RoundState_Win * RoundState_Win::Get()
{
	static RoundState_Win Instance;
	return &Instance;
}

void RoundState_Fail::EnterState(class AStandardGameStateBase* SGS)
{
	GET_SPC_FOR_STATE

		if (SPC->GetPlayerPawn())
		{
			SPC->GetPlayerPawn()->ChangeRunningState(ERoundState::Fail);
			SPC->bShowMouseCursor = true;
		}
}

void RoundState_Fail::Update(class AStandardGameStateBase* SGS, float DeltaTime)
{

}

void RoundState_Fail::LeaveState(class AStandardGameStateBase* SGS)
{
	if (SGS)
	{
		SGS->ResetRound();
	}
}

RoundState_Fail * RoundState_Fail::Get()
{
	static RoundState_Fail Instance;
	return &Instance;
}
