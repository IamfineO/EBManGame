// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "StandardGameUI.generated.h"

/**
 * 
 */
UCLASS()
class EBMAN_API UStandardGameUI : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UFUNCTION()
	FText OnGetText();

	UFUNCTION(BlueprintImplementableEvent)
		void BeginRound();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget = true))
	class UTextBlock* RemainCoinInfoTextBlock;
};
