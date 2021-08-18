// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

UCLASS()
class EBMAN_API ACoin : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACoin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RotationSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AnimJumpHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AnimTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxAnimTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bPickedUp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FVector PlaceLocation;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USceneComponent* Root;
public:
	UFUNCTION(BlueprintCallable)
		void PickUp();

	UFUNCTION(BlueprintCallable)
		bool UpdateCoinPrepare(float DeltaTime);

};
