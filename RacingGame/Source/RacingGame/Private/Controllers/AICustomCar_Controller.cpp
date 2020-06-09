// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/Controllers/AICustomCar_Controller.h"
#include "../../Public/ActorComponents/ACO_CarEngine.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "../../Public/GameModes/RacingGameGameModeBase.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"


AAICustomCar_Controller::AAICustomCar_Controller()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAICustomCar_Controller::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AIController"));

	ACustomCar* PlayerCar = nullptr;
	PlayerCar = GetPlayerCar();

	if (!PlayerCar)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Car not found!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Car found!: name: %s"), *PlayerCar->GetName());
	}
	if (UGameplayStatics::GetGameMode(GetWorld()))
	{
		AGameModeBase* detectedGameMode = UGameplayStatics::GetGameMode(GetWorld());
		GameMode = Cast<ARacingGameGameModeBase>(detectedGameMode);
	}
}

void AAICustomCar_Controller::MoveTo(FVector targetPos)
{
	//Check if target was reached (overlap)
	if (FVector::Distance(GetControlledCar()->GetActorLocation(), targetPos) < TargetAcceptanceRadius)
	{
		CurrentWaypoint_id++;
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
		crossP.Normalize();
		
		float dotP = FVector::DotProduct(distanceVector, forwardVector);
		float angleDeg = atan2(crossP.Size(), dotP);
		
		float angleDegrees = FMath::RadiansToDegrees(angleDeg);

		UE_LOG(LogTemp, Warning, TEXT("Angle: %f"), angleDegrees);
		if (angleDegrees > 5)
		{
			GetControlledCar()->CarEngine->Steer(-0.5);
			UE_LOG(LogTemp, Warning, TEXT("Turning Left"));
		}
		if (angleDegrees < -5)
		{
			GetControlledCar()->CarEngine->Steer(0.5);
			UE_LOG(LogTemp, Warning, TEXT("Turning Right"));
		}
	}

		GetControlledCar()->CarEngine->Accelerate(0.1f);
}


void AAICustomCar_Controller::Tick(float DeltaTime)
{
	if (GetControlledCar())
	{		
		if (GameMode->WaypointPositions.Num() == 0)
		{
			UE_LOG(LogTemp, Error, TEXT("Waypoint array empty"));
			return;
		}
		
		MoveTo(GameMode->WaypointPositions[CurrentWaypoint_id]);
		
		/*if (result == EPathFollowingRequestResult::Type::AlreadyAtGoal)
		{
			waypoint_id++;
			if (waypoint_id >= GameMode->WaypointPositions.Num())
			{
				waypoint_id = 0;
			}
		}*/
		//EPathFollowingRequestResult::Type::
	}
}

ACustomCar* AAICustomCar_Controller::GetControlledCar() const
{
	return Cast<ACustomCar>(GetPawn());
}

ACustomCar * AAICustomCar_Controller::GetPlayerCar() const
{
	return Cast<ACustomCar>(GetWorld()->GetFirstPlayerController()->GetPawn());
}