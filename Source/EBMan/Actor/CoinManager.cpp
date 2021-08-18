// Fill out your copyright notice in the Description page of Project Settings.


#include "EBMan/Actor/CoinManager.h"
#include "Components/BoxComponent.h"
#include "EBMan/Actor/Coin.h"
#include "EBMan/GamePlay/StandardGameStateBase.h"
#include "DrawDebugHelpers.h"

// Sets default values
ACoinManager::ACoinManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VolumeBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxVolume"));
	SetRootComponent(VolumeBox);

	CoinGapDistance = 100.f;
}

// Called when the game starts or when spawned
void ACoinManager::BeginPlay()
{
	Super::BeginPlay();
	if (GetWorld()) {
		AStandardGameStateBase* SGS = Cast<AStandardGameStateBase>(GetWorld()->GetGameState());
		if (SGS) {
			SGS->SetCoinManager(this);
		}
	}

}

void ACoinManager::BeginDestroy()
{
	CleanRestCoins();

	Super::BeginDestroy();
}

// Called every frame
void ACoinManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACoinManager::SpawnCoin()
{
	UWorld* World = GetWorld();
	if (nullptr == World) { return; }

	const float Width = VolumeBox->GetScaledBoxExtent().Y * 2;
	const float Length = VolumeBox->GetScaledBoxExtent().X * 2;

	const int32 XSum = FMath::TruncToInt(Length / CoinGapDistance);
	const int32 YSum = FMath::TruncToInt(Width / CoinGapDistance);

	FHitResult Hit;
	FVector LeftBottom = GetActorLocation();
	//LeftBottom.X = LeftBottom.X - Length / 2 + CoinGapDistance / 2; //从中间找到最边缘，然后加半个Coin间隔
	//LeftBottom.Y = LeftBottom.Y - Length / 2 + CoinGapDistance / 2;

	LeftBottom.X = LeftBottom.X - Length / 2 + CoinGapDistance / 2; //从中间找到最边缘，然后加半个Coin间隔
	LeftBottom.Y = LeftBottom.Y - Length / 2 - CoinGapDistance / 2;

	FVector Start = LeftBottom;
	FVector End = Start;

	for (int32 X = 0; X < XSum; ++X)
	{
		for (int32 Y = 0; Y < YSum; ++Y)
		{
			Start.X = LeftBottom.X + X * CoinGapDistance;
			Start.Y = LeftBottom.Y + Y * CoinGapDistance;
			End = Start;

			End.Z -= 1000.f;
			World->LineTraceSingleByChannel(Hit, Start, End, ECC_WorldStatic);
			//DrawDebugLine(World, Start, End, FColor::Red, false, 60.f);
			//if (Hit.bBlockingHit) {
			//	DrawDebugPoint(World, Hit.Location, 10.f, FColor::Red, true);
			//}
			if (Hit.bBlockingHit && Hit.Location.Z < (MarkPoint.Z + GetActorLocation().Z))
			{
				ACoin* Coin = Cast<ACoin>(World->SpawnActor(CoinClass, &Start));
				if (Coin)
				{
					FVector PlaceLocation = Hit.Location;
					PlaceLocation.Z += CoinGapDistance / 2;
					Coin->PlaceLocation = PlaceLocation;
					CoinList.Add(Coin);
				}
			}
		}
	}
}

void ACoinManager::CleanRestCoins()
{
	if (CoinList.Num() > 0)
	{
		for (ACoin* PendingKillCoin : CoinList)
		{
			if (PendingKillCoin)
			{
				PendingKillCoin->Destroy();
			}
		}
	}
}

bool ACoinManager::UpdateCoinPrepare(float DeltaTime)
{
	bool bFinished = true;
	for (ACoin* Coin : CoinList)
	{
		if (Coin) {
			bool bOk = Coin->UpdateCoinPrepare(DeltaTime);
			if (false == bOk) {
				bFinished = false;
			}
		}
	}
	return bFinished;
}

