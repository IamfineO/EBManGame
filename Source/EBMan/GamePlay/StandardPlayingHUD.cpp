// Fill out your copyright notice in the Description page of Project Settings.


#include "EBMan/GamePlay/StandardPlayingHUD.h"
#include "EBMan/UMG/StandardGameUI.h"

void AStandardPlayingHUD::BeginPlay()
{

}

void AStandardPlayingHUD::BeginRound()
{
	if (nullptr == StandardGameUI)
	{
		StandardGameUI = CreateWidget<UStandardGameUI>(PlayerOwner, StandardGameUIClass);
	}
	if (StandardGameUI)
	{
		StandardGameUI->AddToViewport();
		StandardGameUI->BeginRound();
	}
}

void AStandardPlayingHUD::ReturnToMainMenu()
{
	StandardGameUI->RemoveFromParent();
}
