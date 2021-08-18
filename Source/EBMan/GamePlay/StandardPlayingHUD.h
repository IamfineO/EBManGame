// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "StandardPlayingHUD.generated.h"

/**
 * 
 */
UCLASS()
class EBMAN_API AStandardPlayingHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UStandardGameUI> StandardGameUIClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStandardGameUI* StandardGameUI;

	void BeginRound();

	UFUNCTION(BlueprintCallable)
	void ReturnToMainMenu();
};
