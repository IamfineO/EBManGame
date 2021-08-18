// Fill out your copyright notice in the Description page of Project Settings.


#include "EBMan/UMG/StandardGameUI.h"
#include "Kismet/GameplayStatics.h"
#include "EBMan/GamePlay/StandardGameStateBase.h"


void UStandardGameUI::NativeConstruct()
{
	RemainCoinInfoTextBlock->TextDelegate.BindUFunction(this, TEXT("OnGetText"));
	RemainCoinInfoTextBlock->SynchronizeProperties();
}

FText UStandardGameUI::OnGetText()
{
	AStandardGameStateBase* SGS = Cast<AStandardGameStateBase>(UGameplayStatics::GetGameState(this));
	if (SGS)
	{
		return FText::FromString(SGS->RunInfoString);
	}
	else
		return FText::FromString(TEXT("Coin get error!!!"));
}
