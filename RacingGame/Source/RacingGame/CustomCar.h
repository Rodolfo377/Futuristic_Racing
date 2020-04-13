// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CustomCar.generated.h"


class USphereComponent;
class USpringArmComponent;
class UCameraComponent;

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

	//Raycast to the floor to apply thrusters
	//FHitResult RaycastToFloor();
	void Accelerate(float AxisValue);
	void Steer(float AxisValue);
	void ApplySideFriction();
	//Adds a quick counter-clockwise rotation to the vehicle - Ship-Track alignment Testing purposes
	void LeftBarrelRoll();
	//Adds a quick clockwise rotation to the vehicle - Ship-Track alignment Testing purposes
	void RightBarrelRoll();

	//Here the banking, tricks and other cosmetic transformations will be applied, without affecting the core movement of the ship
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ShipBody = nullptr;

	//Here the acceleration, steering and friction will be applied
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ShipCore = nullptr;

	UPROPERTY(EditAnywhere)
	bool sideFrictionDraw = false;


	UPROPERTY(EditAnywhere)
	double Acceleration = 600000.0;
	UPROPERTY(VisibleAnywhere)
	double SteerRate = 1.0;
	UPROPERTY(VisibleAnywhere)
	double SteerTorque = 100000000.0;
	UPROPERTY(VisibleAnywhere)
	double BankingTorque = 50000000.0;

	UPROPERTY(EditAnywhere)
	double SideFriction = 1000;
	//twice the acceleration of normal gravity

	FVector CurrentVelocity;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	
	/*void ApplyFriction();
	void ApplySidewaysFriction();

	//Should be twice as strong as normal gravity. Will always pull the ship down on its local vetor space.
	void ApplyCustomGravity();*/
};
