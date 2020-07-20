// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/Controllers/AICustomCar_Controller.h"
#include "../../Public/ActorComponents/ACO_CarEngine.h"
#include "../../Public/GameModes/RacingGameGameModeBase.h"

#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "Public/Utilities/DebugLogger.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"



void AAICustomCar_Controller::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("AIController"));

	ControlledCar = GetControlledCar();
	ensureAlways(ControlledCar);

	ControlledCar->Init();

	if (UGameplayStatics::GetGameMode(GetWorld()))
	{
		AGameModeBase* detectedGameMode = UGameplayStatics::GetGameMode(GetWorld());
		GameMode = Cast<ARacingGameGameModeBase>(detectedGameMode);
	}
}

void AAICustomCar_Controller::Update()
{
	if (GetControlledCar()->IsValidLowLevel())
	{
		if (GameMode->ArrayOfWaypoints.Num() == 0)
		{
			UE_LOG(LogTemp, Error, TEXT("Waypoint array empty"));
			return;
		}

		MoveToTarget(GameMode->ArrayOfWaypoints[CurrentWaypoint_id].WorldPosition);
		ControlledCar->Update();
	}
}


AAICustomCar_Controller::AAICustomCar_Controller()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AAICustomCar_Controller::MoveToTarget(FVector targetPos)
{
	float TargetAcceptanceRadius = GameMode->ArrayOfWaypoints[CurrentWaypoint_id].TargetReachedRadius;
	float SteeringRadius = GameMode->ArrayOfWaypoints[CurrentWaypoint_id].SteeringDetectionRadius;
	float distance = FVector::Distance(GetControlledCar()->GetActorLocation(), targetPos);
	//Check if target was reached (overlap)
	if (distance < SteeringRadius && distance > TargetAcceptanceRadius)
	{
		GetControlledCar()->CarEngine->Accelerate(0.05f);
	
		
	}
	else if (distance < TargetAcceptanceRadius)
	{
		CurrentWaypoint_id++;
		if (CurrentWaypoint_id == GameMode->ArrayOfWaypoints.Num())
		{
			CurrentWaypoint_id = 0;
		}
	
	}
	else
	{
		FVector vehiclePos = GetControlledCar()->GetActorLocation();
   		FVector distanceVector = (targetPos - GetControlledCar()->GetActorLocation());
		distanceVector.Normalize();
		FVector forwardVector = GetControlledCar()->GetActorForwardVector();
		forwardVector.Normalize();

		if (PathFollowingDebugDraw)
		{
			DrawDebugLine(GetWorld(), vehiclePos, vehiclePos + forwardVector * 300, FColor::Cyan, false, 0, 0, 5);
			DrawDebugLine(GetWorld(), vehiclePos, targetPos, FColor::Green, false, 0, 0, 5);
		}
		
		//TODO: Accelerate and Steer car towards targetPos
		FVector crossP = FVector::CrossProduct(distanceVector, forwardVector);
		FVector upVector = GetControlledCar()->GetActorUpVector();

		float dotTurning = FVector::DotProduct(crossP, upVector);

		if (dotTurning > 0.2)
		{
			GetControlledCar()->CarEngine->Steer(-0.5);
		}
		if (dotTurning < -0.2)
		{
			GetControlledCar()->CarEngine->Steer(0.5);
		}
		GetControlledCar()->CarEngine->Accelerate(0.5f);
	}		
}


ACustomCar* AAICustomCar_Controller::GetControlledCar()
{
	return Cast<ACustomCar>(GetPawn());
}

void AAICustomCar_Controller::SetGameMode(ARacingGameGameModeBase * _GameMode)
{
	GameMode = _GameMode;
}

void AAICustomCar_Controller::SetControlledCar(ACustomCar * _Car)
{
	ControlledCar = _Car;
}
