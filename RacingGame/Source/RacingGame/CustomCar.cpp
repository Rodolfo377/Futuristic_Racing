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
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"

#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))

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
	
	//MovementComponent->AddInputVector(FVector(GetActorForwardVector()*Acceleration*AxisValue), true);
	//MovementComponent->AddInputVector(FVector(1, 0, 0), true);
	//SphereComponent->AddForce(FVector(GetActorForwardVector()*Acceleration*AxisValue));
	ShipCore->AddForce(FVector(GetActorForwardVector()*Acceleration*AxisValue));
	
}

void ACustomCar::Steer(float AxisValue)
{
	//steering
	ShipCore->AddTorque(GetActorUpVector()*SteerTorque*SteerRate*AxisValue);

	//banking
	FQuat banking = FQuat(ShipCore->GetForwardVector(), (60)*(PI/180));
	

	//ShipBody->AddWorldRotation(banking);
	//ShipBody->SetWorldRotation(banking);	
	//ShipBody->AddRelativeRotation(FQuat(GetActorRotation())*banking);
	ShipBody->SetRelativeRotation(FQuat::Slerp(FQuat(ShipBody->RelativeRotation), FQuat(FRotator(0, 0, 45*AxisValue)), 0.01));

	//Quat(GetActorRotation), FQuat(FRotator(0, 0, 30 * AxisValue), 0.1)
	/*FVector fwd = GetActorForwardVector();
	UE_LOG(LogTemp, Warning, TEXT(""))
	
		printFString()

	FQuat currentRotation = FQuat(ShipBody->GetComponentRotation());
	FQuat desiredRotation = FQuat(GetActorForwardVector(),
		FMath::DegreesToRadians(AxisValue*(-30)));

	//ShipBody->AddWorldRotation(FQuat::Slerp(currentRotation, desiredRotation, 0.01));
	ShipBody->SetWorldRotation(FQuat::Slerp(currentRotation, desiredRotation, 0.01));*/

}

void ACustomCar::ApplySideFriction()
{
	float fwdVelocityAmount = FVector::DotProduct(GetVelocity(), GetActorForwardVector());
	FVector fwdVelocity = fwdVelocityAmount * GetActorForwardVector();
	float rightVelocityAmount = FVector::DotProduct(GetVelocity(), GetActorRightVector());
	FVector rightVelocity = rightVelocityAmount * GetActorRightVector();
	
	ShipCore->AddForce(SideFriction*(-1)*rightVelocity);


}



void ACustomCar::LeftBarrelRoll()
{
	UE_LOG(LogTemp, Warning, TEXT("Left Barrel Roll"));
	ShipCore->AddTorque(GetActorForwardVector()*SteerTorque*SteerRate*(BarrelRollTorque));
}

void ACustomCar::RightBarrelRoll()
{
	UE_LOG(LogTemp, Warning, TEXT("Right Barrel Roll"));
	ShipCore->AddTorque(GetActorForwardVector()*SteerTorque*SteerRate*(-BarrelRollTorque));
}



