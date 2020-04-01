// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "DrawDebugHelpers.h"
#include "ACO_Hover.generated.h"

class ACustomCar;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RACINGGAME_API UACO_Hover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACO_Hover();
	void SetupInputComponent();
	void SetupPhysicsHandle();
	void PIDControl();
	void ApplyHoverForce();
	void ApplyCustomGravity();
	void AlignShipTrack();

	FVector GetReachLineStart();
	FVector GetReachLineEnd();
	FHitResult RaycastToFloor();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	AActor* Owner = nullptr;

	ACustomCar* FlyingCar = nullptr;

	UPROPERTY(VisibleAnywhere)
		UInputComponent* InputComponent = nullptr;

	///PID Control Variables
	UPROPERTY(EditAnywhere)
		//Proportional gain
		double Kp = 5;
	UPROPERTY(EditAnywhere)
		//Integral gain
		double Ki = 2;
	UPROPERTY(EditAnywhere)
		//Derivative gain
		double Kd = 1;
	UPROPERTY(EditAnywhere)
		//aka: setpoint
		double Setpoint = 200;
	UPROPERTY(EditAnywhere)
		//aka: min_control
		double MinControl = 0.9;
	UPROPERTY(EditAnywhere)
		//aka: max_control
		double MaxControl = 1;
	UPROPERTY(EditAnywhere)
		//aka: T
		double TimeSample = 15;

	///Hovering Variables
	UPROPERTY(EditAnywhere)
		double FallGravity = 80.0;
	UPROPERTY(EditAnywhere)
		double HoverForceAmount = 300000.0;
	UPROPERTY(EditAnywhere)
		double HoverGravity = 20.0;
	UPROPERTY(EditAnywhere)
		double RaycastReach = 50.0;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	///PID control variables
	double TotalError = 0;
	double LastError = 0;
	//sensed_output
	double CurrentVehicleHeight = 0;
	double ControlSignal = 0;
};
