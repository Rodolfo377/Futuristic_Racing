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
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupInputComponent();
	void PIDControl();
	void ApplyHoverForce();
	void ApplyCustomGravity();
	void AlignShipTrack();

	FVector GetReachLineStart(FVector offset);
	FVector GetReachLineEnd(FVector startPos);
	FHitResult RaycastToFloor(FVector offset);

	// Called every frame


	

	ACustomCar* Owner = nullptr;

	UPROPERTY(VisibleAnywhere)
	UInputComponent* InputComponent = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PID Control Variables")
		//Proportional gain
		float Kp = 0.1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PID Control Variables")
		//Integral gain
		float Ki = 0.0002;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PID Control Variables")
		//Derivative gain
		float Kd = 0.01;
	UPROPERTY(EditAnywhere, Category = "PID Control Variables")
		//aka: setpoint
		float Setpoint = 200;
	UPROPERTY(EditAnywhere, Category = "PID Control Variables")
		//aka: min_control
		float MinControl = -4;
	UPROPERTY(EditAnywhere, Category = "PID Control Variables")
		//aka: max_control
		float MaxControl = 4;
	UPROPERTY(VisibleAnywhere, Category = "PID Control Variables")
		//aka: T
		float TimeSample = 0.015;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PID Control Variables")
		float ControlSignal = 0;
	
	UPROPERTY(EditAnywhere, Category = "Hovering Variables")
		double FallGravity = 1200000.0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly , Category = "Hovering Variables")
		float HoverForceAmount = 1200000.0;
	UPROPERTY(VisibleAnywhere, Category = "Hovering Variables")
		double HoverGravity = 2000.0;
	UPROPERTY(VisibleAnywhere, Category = "Hovering Variables")
		double RaycastReach = 400.0;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debugging")
		float CustomGravityMagnitude = 0;

	//Tweakable value for pitch alignment with track
	UPROPERTY(EditAnywhere, Category = "Vehicle-Track Alignment")
		double TorquePitchAdjust = 35;

	//Tweakable value for roll alignment with track
	UPROPERTY(EditAnywhere, Category = "Vehicle-Track Alignment")
		double TorqueRollAdjust = 10;

	//Order of magnitude of Torque alignment - should NOT be changed
	UPROPERTY(EditAnywhere, Category = "Vehicle-Track Alignment")
		double TorqueAlignScale = 1000000.0;

	UPROPERTY(EditAnywhere, Category = "Vehicle-Track Alignment")
		double GravityRaycastReach = 500;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	///PID control variables
	float lastProportional = 0;
	float integral = 0;

	double TotalError = 0;
	double LastError = 0;
	double CurrentVehicleHeight = 0;
	FVector downwardsForce;
	FVector TempGroundNormal;


};