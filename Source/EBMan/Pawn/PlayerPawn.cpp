// Fill out your copyright notice in the Description page of Project Settings.


#include "EBMan/Pawn/PlayerPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EBMan/Actor/Coin.h"
#include "EBMan/Actor/CrossRoad.h"
#include "EBMan/Pawn/BaseMonstyerPawn.h"
#include "EBMan/GamePlay/StandardGameStateBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(RootCapsule);
	RootCapsule->SetCapsuleRadius(40.f);
	RootCapsule->SetCapsuleHalfHeight(90.f);

	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));
	PawnMesh->SetupAttachment(RootCapsule);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));
	PawnCamera->SetupAttachment(CameraBoom);

	MoveSpeed = FVector::ZeroVector;

	SpeedScale = 200.f;
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		GetWorld()->GetFirstPlayerController()->Possess(this);
	}
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MoveSpeed != FVector::ZeroVector)
	{
		FVector OldLocation = GetActorLocation();
		FVector TargetLocation = OldLocation + MoveSpeed * SpeedScale * DeltaTime;
		if (bPrepareTurning)
		{
			if (MoveSpeed.X != 0 && GetActorLocation().Y != TurningPoint.Y)
			{
				const float XMoveSpeed = FMath::Abs(MoveSpeed.X * SpeedScale);
				TargetLocation.Y = FMath::FInterpConstantTo(GetActorLocation().Y, TurningPoint.Y, DeltaTime, XMoveSpeed);
				TargetLocation.X = GetActorLocation().X;
			}
			if (MoveSpeed.Y != 0 && GetActorLocation().X != TurningPoint.X)
			{
				const float YMoveSpeed = FMath::Abs(MoveSpeed.Y * SpeedScale);
				TargetLocation.X = FMath::FInterpConstantTo(GetActorLocation().X, TurningPoint.X, DeltaTime, YMoveSpeed);
				if (!FMath::IsNearlyEqual(TargetLocation.X, TurningPoint.X))
				{
					TargetLocation.Y = GetActorLocation().Y;
				}
			}
		}
		SetActorLocation(TargetLocation, true);
	}
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerPawn::MoveForward);
		PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerPawn::MoveRight);
	}
}

void APlayerPawn::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//拾取金币
	ACoin* Coin = Cast<ACoin>(OtherActor);
	if (Coin)
	{
		Coin->PickUp();
	}

	//碰到怪物，游戏失败
	ABaseMonstyerPawn* Monstyer = Cast<ABaseMonstyerPawn>(OtherActor);
	if (Monstyer)
	{
		AStandardGameStateBase* SGS = Cast<AStandardGameStateBase>(UGameplayStatics::GetGameState(this));
		if (SGS)
		{
			SGS->ChangeCurrentRoundState(ERoundState::Fail);
		}
	}

	//进入转弯优化状态
	ACrossRoad* CrossRoad = Cast<ACrossRoad>(OtherActor);
	if (CrossRoad)
	{
		bPrepareTurning = true;
		TurningPoint = CrossRoad->GetActorLocation();
	}
}

void APlayerPawn::NotifyActorEndOverlap(AActor* OtherActor)
{	
	//进入转弯优化状态
	ACrossRoad* CrossRoad = Cast<ACrossRoad>(OtherActor);
	if (CrossRoad)
	{
		if (TurningPoint == CrossRoad->GetActorLocation())
		{
			bPrepareTurning = false;
		}
	}

}

void APlayerPawn::ChangeRunningState(ERoundState NewState)
{
	if (NewState == ERoundState::Running)
	{
		PrimaryActorTick.SetTickFunctionEnable(true);
	}
	else
		PrimaryActorTick.SetTickFunctionEnable(false);
}

void APlayerPawn::MoveForward(float val)
{
	MoveSpeed.X = val;
}

void APlayerPawn::MoveRight(float val)
{
	MoveSpeed.Y = val;
}

