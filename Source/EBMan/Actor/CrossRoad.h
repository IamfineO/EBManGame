// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CrossRoad.generated.h"

UCLASS()
class EBMAN_API ACrossRoad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACrossRoad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* CrossBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ACrossRoad*> NearByCrossRoads;

public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	ACrossRoad* GetNextNearByCrossRoad();

	ACrossRoad* GetRandomCrossRoad();

	UFUNCTION(BlueprintCallable)
	void FindNearByCrossRoads();

	UFUNCTION(BlueprintPure)
	bool IsUsingRandomDirection() { return bUsingRandomDirection; };

private:
	int32 NextCrossRoadIndex;

	bool bUsingRandomDirection;
};
