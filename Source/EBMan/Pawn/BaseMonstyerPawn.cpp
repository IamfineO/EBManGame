// Fill out your copyright notice in the Description page of Project Settings.


#include "EBMan/Pawn/BaseMonstyerPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EBMan/GamePlay/StandardGameStateBase.h"
#include "EBMan/EBGameType.h"

// Sets default values
ABaseMonstyerPawn::ABaseMonstyerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));
	SetRootComponent(PawnMesh);

	MoveSpeed = 300.f;
}

// Called when the game starts or when spawned
void ABaseMonstyerPawn::BeginPlay()
{
	Super::BeginPlay();
	if (nullptr != NextCrossRoad)
	{
		TargetLocation = NextCrossRoad->GetActorLocation();
	}

}

// Called every frame
void ABaseMonstyerPawn::Tick(float DeltaTime)
{
	AStandardGameStateBase* SGS = Cast<AStandardGameStateBase>(UGameplayStatics::GetGameState(this));
	if (SGS && SGS->GetCurrentRoundState() != ERoundState::Running)
	{
		return;
	}
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();

	SetActorLocation(FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, MoveSpeed));

	if (GetActorLocation() == TargetLocation && NextCrossRoad)
	{
		TargetLocation = NextCrossRoad->GetActorLocation();
	}
}

// Called to bind functionality to input
void ABaseMonstyerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseMonstyerPawn::NotifyActorBeginOverlap(AActor* OtherActor)
{
	ACrossRoad* CrossRoad = Cast<ACrossRoad>(OtherActor);
	if (CrossRoad)
	{
		NextCrossRoad = CrossRoad->IsUsingRandomDirection() ? CrossRoad->GetRandomCrossRoad() : CrossRoad->GetNextNearByCrossRoad();
	}
}

