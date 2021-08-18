// Fill out your copyright notice in the Description page of Project Settings.


#include "EBMan/EBMan.h"
#include "EBMan/Actor/CrossRoad.h"
#include "Components/BoxComponent.h"

// Sets default values
ACrossRoad::ACrossRoad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CrossBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CrossBox"));
	SetRootComponent(CrossBox);

	CrossBox->SetGenerateOverlapEvents(true);

	SetActorHiddenInGame(false);
	NextCrossRoadIndex = 0;
	bUsingRandomDirection = false;
}

// Called when the game starts or when spawned
void ACrossRoad::BeginPlay()
{
	Super::BeginPlay();
	
	FindNearByCrossRoads();
	if (NearByCrossRoads.Num() > 2) bUsingRandomDirection = true;
	else
		bUsingRandomDirection = false;
}

// Called every frame
void ACrossRoad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACrossRoad::NotifyActorBeginOverlap(AActor* OtherActor)
{
	
}

ACrossRoad* ACrossRoad::GetNextNearByCrossRoad()
{
	if (NearByCrossRoads.Num() <= 0) {
		return this;
	}
	NextCrossRoadIndex = (NextCrossRoadIndex + 1) % NearByCrossRoads.Num();
	return NearByCrossRoads[NextCrossRoadIndex];
}

ACrossRoad* ACrossRoad::GetRandomCrossRoad()
{
	if (NearByCrossRoads.Num() <= 0) {
		return this;
	}
	NextCrossRoadIndex = FMath::Rand() % NearByCrossRoads.Num();
	return NearByCrossRoads[NextCrossRoadIndex];
}

void ACrossRoad::FindNearByCrossRoads()
{
	UWorld* World = GetWorld();
	if (!World) { return; }
	
	TArray<FHitResult> HitResult;
	FCollisionQueryParams QueryParams;

	QueryParams.AddIgnoredActor(this);
	FVector ActorLocation = GetActorLocation();

	//向 上 方做射线检测
	FVector Target = ActorLocation + FVector(2000.f, 0.f, 0.f);
	World->LineTraceMultiByChannel(HitResult, ActorLocation, Target, ECC_CrossRoad, QueryParams);
	ACrossRoad* OtherCrossRoad = nullptr;
	if (HitResult.Num() > 0)
	{
		for (FHitResult Result : HitResult)
		{
			OtherCrossRoad = Cast<ACrossRoad>(Result.GetActor());
			if (OtherCrossRoad)
			{
				NearByCrossRoads.Push(OtherCrossRoad);
				break;
			}
		}
	}

	//向 右 方做射线检测
	Target = ActorLocation + FVector(0.f, 2000.f, 0.f);
	World->LineTraceMultiByChannel(HitResult, ActorLocation, Target, ECC_CrossRoad, QueryParams);
	OtherCrossRoad = nullptr;
	if (HitResult.Num() > 0)
	{
		for (FHitResult Result : HitResult)
		{
			OtherCrossRoad = Cast<ACrossRoad>(Result.GetActor());
			if (OtherCrossRoad)
			{
				NearByCrossRoads.Push(OtherCrossRoad);
				break;
			}
		}
	}

	//向 下 方做射线检测
	Target = ActorLocation + FVector(-2000.f, 0.f, 0.f);
	World->LineTraceMultiByChannel(HitResult, ActorLocation, Target, ECC_CrossRoad, QueryParams);
	OtherCrossRoad = nullptr;
	if (HitResult.Num() > 0)
	{
		for (FHitResult Result : HitResult)
		{
			OtherCrossRoad = Cast<ACrossRoad>(Result.GetActor());
			if (OtherCrossRoad)
			{
				NearByCrossRoads.Push(OtherCrossRoad);
				break;
			}
		}
	}

	//向 左 方做射线检测
	Target = ActorLocation + FVector(0.f, -2000.f, 0.f);
	World->LineTraceMultiByChannel(HitResult, ActorLocation, Target, ECC_CrossRoad, QueryParams);
	OtherCrossRoad = nullptr;
	if (HitResult.Num() > 0)
	{
		for (FHitResult Result : HitResult)
		{
			OtherCrossRoad = Cast<ACrossRoad>(Result.GetActor());
			if (OtherCrossRoad)
			{
				NearByCrossRoads.Push(OtherCrossRoad);
				break;
			}
		}
	}
}

