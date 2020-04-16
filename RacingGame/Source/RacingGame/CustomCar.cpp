// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCar.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"

#define OUT
// Sets default values
ACustomCar::ACustomCar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

void ACustomCar::UpdateCheckpoint(uint32 checkpointId)
{
	if (Checkpoints.size() == 3)
	{
		if ((Checkpoints[0] == 1) && (Checkpoints[1] == 2) && (Checkpoints[2] == 3))
		{
			CurrentLap++;
		}

		if (Checkpoints[2] != checkpointId)
		{
			Checkpoints[0] = Checkpoints[1];
			Checkpoints[1] = Checkpoints[2];
			Checkpoints[2] = checkpointId;
		}
	}
}

// Called when the game starts or when spawned
void ACustomCar::BeginPlay()
{
	Super::BeginPlay();	
	if (!ShipCore->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("ShipCore is not valid!"));
		return;
	}
	if (!ShipBody->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("ShipBody is not valid!"));
		return;
	}
	if (ShipBody->bEditableWhenInherited)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ship body is editable by default"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Ship body is NOT editable by default"))
	}
}



// Called every frame
void ACustomCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	

	ApplySideFriction();	
	//CounterBanking();
}



// Called to bind functionality to input
void ACustomCar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAxis("Accelerate", this, &ACustomCar::Accelerate);
		PlayerInputComponent->BindAxis("Steer", this, &ACustomCar::Steer);
		PlayerInputComponent->BindAction("LeftBarrelRoll", IE_Pressed, this, &ACustomCar::LeftBarrelRoll);
		PlayerInputComponent->BindAction("RightBarrelRoll", IE_Pressed, this, &ACustomCar::RightBarrelRoll);
	}
}


void ACustomCar::Accelerate(float AxisValue)
{
	if (!ShipCore->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("ShipBody is not valid!"));
		return;
	}
	
	//SphereComponent->AddForce(FVector(GetActorForwardVector()*Acceleration*AxisValue));
	ShipCore->AddForce(FVector(GetActorForwardVector()*Acceleration*AxisValue));
	
}

void ACustomCar::Steer(float AxisValue)
{
	
	ShipCore->AddTorque(GetActorUpVector()*SteerTorque*SteerRate*AxisValue);

	double angle = (GetActorRotation().Roll - ShipBody->GetComponentRotation().Roll)*GetWorld()->DeltaTimeSeconds;

	if (BankingDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("Banking"));
		UE_LOG(LogTemp, Warning, TEXT("counter banking angle: %f actor roll: %f, shipBody roll: %f, dt: %f"),
			angle,
			GetActorRotation().Roll,
			ShipBody->GetComponentRotation().Roll,
			GetWorld()->DeltaTimeSeconds);
	}

	//SphereComponent->AddLocalRotation(steer);
	FQuat banking = FQuat(GetActorForwardVector(), -angle +(-5)*AxisValue*GetWorld()->DeltaTimeSeconds);
	ShipBody->AddWorldRotation(banking);

}

void ACustomCar::ApplySideFriction()
{
	float fwdVelocityAmount = FVector::DotProduct(GetVelocity(), GetActorForwardVector());
	FVector fwdVelocity = fwdVelocityAmount * GetActorForwardVector();
	float rightVelocityAmount = FVector::DotProduct(GetVelocity(), GetActorRightVector());
	FVector rightVelocity = rightVelocityAmount * GetActorRightVector();
	
	ShipCore->AddForce(SideFriction*(-1)*rightVelocity);

	DrawDebugLine(GetWorld(),
		GetActorLocation(),
		GetActorLocation() + SideFriction * (-1)*rightVelocity,
		FColor::Red,
		false,
		0,
		0,
		5);

	DrawDebugLine(GetWorld(),
		GetActorLocation(),
		GetActorLocation() + fwdVelocity,
		FColor::Green,
		false,
		0,
		0,
		5);
}

void ACustomCar::LeftBarrelRoll()
{
	UE_LOG(LogTemp, Warning, TEXT("Left Barrel Roll"));
	ShipCore->AddTorque(GetActorForwardVector()*SteerTorque*SteerRate*(-BarrelRollTorque));
}

void ACustomCar::RightBarrelRoll()
{
	UE_LOG(LogTemp, Warning, TEXT("Right Barrel Roll"));
	ShipCore->AddTorque(GetActorForwardVector()*SteerTorque*SteerRate*(BarrelRollTorque));
}



