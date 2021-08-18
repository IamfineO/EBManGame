// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RoundStateMacheine.generated.h"

/**
 * 状态类的基类
 * 提供给RoundStateMachine使用
 */
class EBMAN_API RoundState
{
public:

	virtual void EnterState(class AStandardGameStateBase* SGS) = 0;

	virtual void Update(class AStandardGameStateBase* SGS, float DeltaTime) = 0;

	virtual void LeaveState(class AStandardGameStateBase* SGS) = 0;

};
/**
 * 
 */
UCLASS()
class EBMAN_API URoundStateMacheine : public UObject
{
	GENERATED_BODY()
	
public:
	void InitStateMachine(class AStandardGameStateBase* Owner);

	void UpdateState(float DeltaTime);

	void ChangeState(RoundState* NewState);

protected:

	class AStandardGameStateBase* OwnerActor;

	//当前状态机正在执行的状态
	RoundState* CurrentState;
};

/*
 * 主菜单状态
 */
class EBMAN_API RoundState_InMenu : public RoundState
{
public:
	virtual void EnterState(class AStandardGameStateBase* SGS) override;

	virtual void Update(class AStandardGameStateBase* SGS, float DeltaTime) override;

	virtual void LeaveState(class AStandardGameStateBase* SGS) override;

	static RoundState_InMenu * Get();
};

/*
 * 准备状态
 */
class EBMAN_API RoundState_Preparing : public RoundState
{
public:
	virtual void EnterState(class AStandardGameStateBase* SGS) override;

	virtual void Update(class AStandardGameStateBase* SGS, float DeltaTime) override;

	virtual void LeaveState(class AStandardGameStateBase* SGS) override;

	static RoundState_Preparing * Get();
};

/*
 * 游戏运行状态
 */
class EBMAN_API RoundState_Running : public RoundState
{
public:
	virtual void EnterState(class AStandardGameStateBase* SGS) override;

	virtual void Update(class AStandardGameStateBase* SGS, float DeltaTime) override;

	virtual void LeaveState(class AStandardGameStateBase* SGS) override;

	static RoundState_Running * Get();
};

/*
 * 游戏胜利状态
 */
class EBMAN_API RoundState_Win : public RoundState
{
public:
	virtual void EnterState(class AStandardGameStateBase* SGS) override;

	virtual void Update(class AStandardGameStateBase* SGS, float DeltaTime) override;

	virtual void LeaveState(class AStandardGameStateBase* SGS) override;

	static RoundState_Win * Get();
};

/*
 * 游戏失败状态
 */
class EBMAN_API RoundState_Fail : public RoundState
{
public:
	virtual void EnterState(class AStandardGameStateBase* SGS) override;

	virtual void Update(class AStandardGameStateBase* SGS, float DeltaTime) override;

	virtual void LeaveState(class AStandardGameStateBase* SGS) override;

	static RoundState_Fail * Get();
};