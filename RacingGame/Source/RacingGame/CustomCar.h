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

	void Hovering();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Raycast to the floor to apply thrusters
	FHitResult RaycastToFloor();
	void Accelerate(float AxisValue);
	void Steer(float AxisValue);

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* OurVisibleComponent;
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComponent = nullptr;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComponent = nullptr;
	UPROPERTY(EditAnywhere)
	UCameraComponent* OurCamera = nullptr;

	UPROPERTY(EditAnywhere)
		float FallGravity = 80.0f;
	UPROPERTY(EditAnywhere)
		float HoverForce = 300.0f;
	UPROPERTY(EditAnywhere)
		float HoverGravity = 20.0f;

	UPROPERTY(EditAnywhere)
		float RaycastReach = 50;

	UPROPERTY(EditAnywhere)
		float Acceleration = 0.0f;
	UPROPERTY(EditAnywhere)
	float SteerRate = 0.0f;
	//twice the acceleration of normal gravity
	UPROPERTY(EditAnywhere)
	float CustomGravity = 9.8f*2.0f;

	FVector CurrentVelocity;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	FVector GetReachLineStart();
	FVector GetReachLineEnd();
	void ApplyFriction();
	void ApplySidewaysFriction();

	//Should be twice as strong as normal gravity. Will always pull the ship down on its local vetor space.
	void ApplyCustomGravity();
};
