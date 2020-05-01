// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "ACO_CarEngine.generated.h"


/*This class is responsible for accomodating the following movement functionalities:
-Acceleration
-Steering
-Side Friction
-Barrel Rolling
*/
class ACustomCar;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RACINGGAME_API UACO_CarEngine : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACO_CarEngine();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	//Raycast to the floor to apply thrusters
	//FHitResult RaycastToFloor();
	void Accelerate(float AxisValue);
	void Steer(float AxisValue);
	void ApplySideFriction();

	//Adds a quick counter-clockwise rotation to the vehicle - Ship-Track alignment Testing purposes
	void LeftBarrelRoll();
	//Adds a quick clockwise rotation to the vehicle - Ship-Track alignment Testing purposes
	void RightBarrelRoll();

	ACustomCar* Owner = nullptr;



	UPROPERTY(VisibleAnywhere)
		UInputComponent* InputComponent = nullptr;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;	


	UPROPERTY(EditAnywhere)
		double Acceleration = 600000.0;
	UPROPERTY(EditAnywhere)
		double SteerRate = 3.0;
	UPROPERTY(EditAnywhere)
		double SteerTorque = 10000000.0;
	UPROPERTY(EditAnywhere)
		double BankingTorque = 50000000.0;

	UPROPERTY(EditAnywhere, Category = "Debugging")
		bool BankingDebug = false;
	UPROPERTY(EditAnywhere, Category = "Debugging")
		double BarrelRollTorque = 10;

	UPROPERTY(EditAnywhere)
		double SideFriction = 900;
};

