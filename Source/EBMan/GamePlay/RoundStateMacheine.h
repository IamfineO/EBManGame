// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RoundStateMacheine.generated.h"

/**
 * ״̬��Ļ���
 * �ṩ��RoundStateMachineʹ��
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

	//��ǰ״̬������ִ�е�״̬
	RoundState* CurrentState;
};

/*
 * ���˵�״̬
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
 * ׼��״̬
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
 * ��Ϸ����״̬
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
 * ��Ϸʤ��״̬
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
 * ��Ϸʧ��״̬
 */
class EBMAN_API RoundState_Fail : public RoundState
{
public:
	virtual void EnterState(class AStandardGameStateBase* SGS) override;

	virtual void Update(class AStandardGameStateBase* SGS, float DeltaTime) override;

	virtual void LeaveState(class AStandardGameStateBase* SGS) override;

	static RoundState_Fail * Get();
};