// Fill out your copyright notice in the Description page of Project Settings.


#include "ACO_CarEngine.h"
#include "Components/StaticMeshComponent.h"
#include "CustomCar.h"


// Sets default values for this component's properties
UACO_CarEngine::UACO_CarEngine()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UACO_CarEngine::BeginPlay()
{
	Super::BeginPlay();
	Owner = (ACustomCar*)GetOwner();

	if (!Owner->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("No Owner actor detected!"))
		return;
	}
	// ...
	InputComponent = Owner->FindComponentByClass<UInputComponent>();
}


// Called every frame
void UACO_CarEngine::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	ApplySideFriction();
	// ...
}

void UACO_CarEngine::Accelerate(float AxisValue)
{
	Owner->ShipCore->AddForce(FVector(Owner->GetActorForwardVector()*Acceleration*AxisValue));
	
}

void UACO_CarEngine::Steer(float AxisValue)
{
		//steering
		Owner->ShipCore->AddTorqueInRadians(Owner->GetActorUpVector()*SteerTorque*SteerRate*AxisValue);

		//banking
		FQuat banking = FQuat(Owner->ShipCore->GetForwardVector(), (60)*(PI / 180));
		Owner->ShipBody->SetRelativeRotation(FQuat::Slerp(FQuat(Owner->ShipBody->RelativeRotation), FQuat(FRotator(0, 0, 45 * AxisValue)), 0.01));
}

void UACO_CarEngine::LeftBarrelRoll()
{
	Owner->ShipCore->AddTorqueInRadians(Owner->GetActorForwardVector()*SteerTorque*SteerRate*(BarrelRollTorque));
}

void UACO_CarEngine::RightBarrelRoll()
{
	Owner->ShipCore->AddTorqueInRadians(Owner->GetActorForwardVector()*SteerTorque*SteerRate*(-BarrelRollTorque));
}

void  UACO_CarEngine::ApplySideFriction()
{
	float fwdVelocityAmount = FVector::DotProduct(Owner->GetVelocity(), Owner->GetActorForwardVector());
	FVector fwdVelocity = fwdVelocityAmount * Owner->GetActorForwardVector();
	float rightVelocityAmount = FVector::DotProduct(Owner->GetVelocity(), Owner->GetActorRightVector());
	FVector rightVelocity = rightVelocityAmount * Owner->GetActorRightVector();

	Owner->ShipCore->AddForce(SideFriction*(-1)*rightVelocity);
}




