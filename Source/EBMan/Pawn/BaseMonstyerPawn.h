// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EBMan/Actor/CrossRoad.h"
#include "BaseMonstyerPawn.generated.h"

UCLASS()
class EBMAN_API ABaseMonstyerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseMonstyerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* PawnMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector TargetLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ACrossRoad* NextCrossRoad;

public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
