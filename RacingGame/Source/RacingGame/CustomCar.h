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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ShipBody = nullptr;


	UPROPERTY(VisibleAnywhere)
	double Acceleration = 300000.0;
	UPROPERTY(VisibleAnywhere)
	double SteerRate = 1.0;
	UPROPERTY(VisibleAnywhere)
	double SteerTorque = 100000000.0;
	UPROPERTY(VisibleAnywhere)
	double BankingTorque = 10000.0;
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
