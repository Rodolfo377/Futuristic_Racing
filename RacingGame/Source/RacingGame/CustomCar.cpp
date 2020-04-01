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

// Called when the game starts or when spawned
void ACustomCar::BeginPlay()
{
	Super::BeginPlay();	
}



// Called every frame
void ACustomCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
		
	if (!ShipBody->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("ShipBody is not valid!"));
		return;
	}
		
}



// Called to bind functionality to input
void ACustomCar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAxis("Accelerate", this, &ACustomCar::Accelerate);
		PlayerInputComponent->BindAxis("Steer", this, &ACustomCar::Steer);
	}
}


void ACustomCar::Accelerate(float AxisValue)
{
	if (!ShipBody->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("ShipBody is not valid!"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("CustomCar.cpp accelerating: Acceleration: %f"), Acceleration)
	//SphereComponent->AddForce(FVector(GetActorForwardVector()*Acceleration*AxisValue));
	ShipBody->AddForce(FVector(GetActorForwardVector()*Acceleration*AxisValue));
	
}

void ACustomCar::Steer(float AxisValue)
{
	if (!ShipBody->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("ShipBody is not valid!"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("CustomCar.cpp steering"))
	FRotator steer = FRotator(0, AxisValue * SteerRate, 0);
	//SphereComponent->AddLocalRotation(steer);
	ShipBody->AddLocalRotation(steer);
}

