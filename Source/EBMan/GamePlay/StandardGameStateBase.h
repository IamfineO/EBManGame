// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "EBMan/EBGameType.h"
#include "EBMan/Actor/CoinManager.h"
#include "StandardGameStateBase.generated.h"

/**
 *
 */
UCLASS()
class EBMAN_API AStandardGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	AStandardGameStateBase();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	//��ʼ���غ�
	void BeginRound();

public:


	//����״̬��
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class URoundStateMacheine* FSM;

	//��ǰ�Ĺؿ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		EGameRound CurrentRoundIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		EGameRound PendingRoundIndex;

	//��ǰ������ʣ������������Ϊ0ʱ�򱾻غϽ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 CoinSumRemain;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FString RunInfoString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float PrepareTime;

protected:
	//��ǰ�غϵ�����״̬
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		ERoundState CurrentRoundState;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class ACoinManager* CoinManager;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FName LevelOneName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FName LevelOneNightName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FName LevelTwoName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FName LevelTwoNightName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FName LevelThreeName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FName LevelThreeNightName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FName LevelFourName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FName LevelFourNightName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FName LevelFiveName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FName LevelFiveNightName;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FName CurrentLevelName;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FName PendingLevelName;
public:
	UFUNCTION(BlueprintPure)
		ERoundState GetCurrentRoundState() { return CurrentRoundState; }

	UFUNCTION(BlueprintCallable)
		void ChangeCurrentRoundState(ERoundState NewState);

	class RoundState* RoundStateFromEnum(ERoundState InState);

	FName LevelNameFromEnum(EGameRound InRound);

	class ACoinManager* GetCoinManager() { return CoinManager; }

	void SetCoinManager(ACoinManager* InManager) { CoinManager = InManager; }

	UFUNCTION(BlueprintPure)
	EGameRound GetNextRoundIndex();

	UFUNCTION(BlueprintCallable)
		void ResetRound();

	UFUNCTION(BlueprintCallable, Exec)
		void OpenRound(EGameRound InRound);

	UFUNCTION()
		void UnloadRoundLevel();

	UFUNCTION()
		void OnUnloadLevelComplete();

	UFUNCTION()
		void OnLoadLevelComplete();

private:
	void InitLevelName();
};
