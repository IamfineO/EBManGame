// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EBMan/EBGameType.h"
#include "PlayerPawn.generated.h"

UCLASS()
class EBMAN_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	void ChangeRunningState(ERoundState NewState);
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UCapsuleComponent* RootCapsule;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* PawnMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UCameraComponent* PawnCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FVector MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SpeedScale;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bPrepareTurning;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FVector TurningPoint;
private:
	void MoveForward(float val);

	void MoveRight(float val);
};
