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
	void AlignShipTrack(FVector groundNormal);

	FVector GetReachLineStart();
	FVector GetReachLineEnd();
	FHitResult RaycastToFloor();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	AActor* Owner = nullptr;

	ACustomCar* FlyingCar = nullptr;

	UPROPERTY(VisibleAnywhere)
		UInputComponent* InputComponent = nullptr;


	UPROPERTY(EditAnywhere, Category = "PID Control Variables")
		//Proportional gain
		double Kp = 10;
	UPROPERTY(EditAnywhere, Category = "PID Control Variables")
		//Integral gain
		double Ki = 2;
	UPROPERTY(EditAnywhere, Category = "PID Control Variables")
		//Derivative gain
		double Kd = 1;
	UPROPERTY(EditAnywhere, Category = "PID Control Variables")
		//aka: setpoint
		double Setpoint = 300;
	UPROPERTY(EditAnywhere, Category = "PID Control Variables")
		//aka: min_control
		double MinControl = 0.9;
	UPROPERTY(VisibleAnywhere, Category = "PID Control Variables")
		//aka: max_control
		double MaxControl = 1;
	UPROPERTY(VisibleAnywhere, Category = "PID Control Variables")
		//aka: T
		double TimeSample = 15;

	
	UPROPERTY(VisibleAnywhere, Category = "Hovering Variables")
		double FallGravity = 1000000.0;
	UPROPERTY(EditAnywhere, Category = "Hovering Variables")
		double HoverForceAmount = 400000.0;
	UPROPERTY(VisibleAnywhere, Category = "Hovering Variables")
		double HoverGravity = 2000.0;
	UPROPERTY(VisibleAnywhere, Category = "Hovering Variables")
		double RaycastReach = 400.0;


	//Tweakable value for pitch alignment with track
	UPROPERTY(EditAnywhere, Category = "Vehicle-Track Alignment")
		double TorquePitchAdjust = 5;

	//Tweakable value for roll alignment with track
	UPROPERTY(EditAnywhere, Category = "Vehicle-Track Alignment")
		double TorqueRollAdjust = 10;

	//Order of magnitude of Torque alignment - should NOT be changed
	UPROPERTY(EditAnywhere, Category = "Vehicle-Track Alignment")
		double TorqueAlignScale = 10000000.0;
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
	FHitResult m_Hit;
	double slerpRotT = 0;

};
