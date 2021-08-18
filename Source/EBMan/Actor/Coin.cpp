// Fill out your copyright notice in the Description page of Project Settings.


#include "EBMan/Actor/Coin.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EBMan/GamePlay/StandardGameStateBase.h"

// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Root);
	Mesh->SetupAttachment(Root);

	RotationSpeed = 300.f;

	bPickedUp = false;
	AnimJumpHeight = 200.f;
	AnimTime = 0.f;
	MaxAnimTime = 1.f;
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Mesh->AddRelativeRotation(FRotator(0.f, RotationSpeed * DeltaTime, 0.f));

	if (bPickedUp)
	{
		FVector AnimLocation = GetActorLocation();
		float SinForZ = FMath::Sin(AnimTime / MaxAnimTime * PI) * AnimJumpHeight;
		AnimLocation.Z += SinForZ;
		Mesh->SetWorldLocation(AnimLocation);

		AnimTime += DeltaTime;
		if (AnimTime >= MaxAnimTime)
		{
			Destroy();
		}
	}
}

void ACoin::PickUp()
{
	AStandardGameStateBase* SGS = Cast<AStandardGameStateBase>(UGameplayStatics::GetGameState(this));
	if (SGS && bPickedUp == false)
	{
		SGS->CoinSumRemain--;
	}
	bPickedUp = true;
}

bool ACoin::UpdateCoinPrepare(float DeltaTime)
{
	FVector DeltaLocation = FMath::VInterpConstantTo(GetActorLocation(), PlaceLocation, DeltaTime, 100.f);
	if (DeltaLocation != PlaceLocation) {
		SetActorLocation(DeltaLocation);
		return false;
	}
	return true;
}