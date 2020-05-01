// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ACO_CollidingCarMovement.h"
#include <vector>
#include "CustomCar.generated.h"


class USphereComponent;
class USpringArmComponent;
class UCameraComponent;
class UACO_CarEngine;


UCLASS()
class RACINGGAME_API ACustomCar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACustomCar();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//void Hovering();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	//Here the banking, tricks and other cosmetic transformations will be applied, without affecting the core movement of the ship
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* ShipBody = nullptr;

	//Here the acceleration, steering and friction will be applied
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* ShipCore = nullptr;




	UPROPERTY(EditAnywhere)
		bool SideFrictionDraw = false;

	UFUNCTION(BlueprintCallable)
		int CheckCurrentLap() { return CurrentLap; }
	//Updates array of checkpoints completed when a custom car object overlaps with a checkpoint object. 
	//FIFO container.
	//@ id: unique id of checkpoint [1,3]
	void UpdateCheckpoint(uint32 checkpointId);


	
	//twice the acceleration of normal gravity

	FVector CurrentVelocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay")
		int CurrentLap = 1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	std::vector<int> Checkpoints = { 0 ,0 ,0 };

	
	//Component that will handle input-based movement: acceleration, steering, side friction. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACO_CarEngine *CarEngine = nullptr;
};
