// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoinManager.generated.h"

UCLASS()
class EBMAN_API ACoinManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoinManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void BeginDestroy() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBoxComponent* VolumeBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ACoin> CoinClass;

	//½ð±Ò¼ä¾à
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CoinGapDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget = true))
		FVector MarkPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<class ACoin*> CoinList;
public:

	UFUNCTION(BlueprintCallable)
	void SpawnCoin();

	UFUNCTION(BlueprintCallable)
	void CleanRestCoins();

	UFUNCTION(BlueprintCallable)
	bool UpdateCoinPrepare(float DeltaTime);

	UFUNCTION(BlueprintPure)
	int32 GetCoinSum() { return CoinList.Num(); }
};
