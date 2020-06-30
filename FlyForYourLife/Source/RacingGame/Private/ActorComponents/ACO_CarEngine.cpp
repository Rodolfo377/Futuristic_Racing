// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/ActorComponents/ACO_CarEngine.h"
#include "Components/StaticMeshComponent.h"
#include "../../Public/Pawns/CustomCar.h"


void UACO_CarEngine::Init()
{
	Owner = (ACustomCar*)GetOwner();
	ensureAlways(Owner);
}

void UACO_CarEngine::Update()
{
	ApplySideFriction();
}

// Sets default values for this component's properties
UACO_CarEngine::UACO_CarEngine()
{
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UACO_CarEngine::Accelerate(float AxisValue)
{
	ensureAlways(Owner->ShipCore);
	Owner->ShipCore->AddForce(FVector(Owner->GetActorForwardVector()*Acceleration*AxisValue));
	
}

void UACO_CarEngine::Steer(float AxisValue)
{
	//steering
	ensureAlways(Owner->ShipCore);
	ensureAlways(Owner->ShipBody);
	Owner->ShipCore->AddTorqueInRadians(Owner->GetActorUpVector()*SteerTorque*SteerRate*AxisValue);

	//banking
	FQuat banking = FQuat(Owner->ShipCore->GetForwardVector(), (60)*(PI / 180));
	Owner->ShipBody->SetRelativeRotation(FQuat::Slerp(FQuat(Owner->ShipBody->RelativeRotation), FQuat(FRotator(0, 0, 70 * AxisValue)), 0.01));
}

void UACO_CarEngine::LeftBarrelRoll()
{

		
}

void UACO_CarEngine::RightBarrelRoll()
{
	
}

void  UACO_CarEngine::ApplySideFriction()
{
	float fwdVelocityAmount = FVector::DotProduct(Owner->GetVelocity(), Owner->GetActorForwardVector());
	FVector fwdVelocity = fwdVelocityAmount * Owner->GetActorForwardVector();
	float rightVelocityAmount = FVector::DotProduct(Owner->GetVelocity(), Owner->GetActorRightVector());
	FVector rightVelocity = rightVelocityAmount * Owner->GetActorRightVector();

	Owner->ShipCore->AddForce(SideFriction*(-1)*rightVelocity);
}




