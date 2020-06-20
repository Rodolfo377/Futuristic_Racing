// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/ActorComponents/ACO_Position.h"
#include "../../Public/Pawns/CustomCar.h"
#include "../../Public/GameModes/RacingGameGameModeBase.h"
#include "../../Public/Utilities/DebugLogger.h"
#include "../../Public/Controllers/AICustomCar_Controller.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Components/SplineComponent.h"
// Sets default values for this component's properties
UACO_Position::UACO_Position()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UACO_Position::BeginPlay()
{
	Super::BeginPlay();
	Owner = (ACustomCar*)GetOwner();
	ensureAlways(Owner);


	if (UGameplayStatics::GetGameMode(GetWorld()))
	{
		AGameModeBase* detectedGameMode = UGameplayStatics::GetGameMode(GetWorld());
		GameMode = Cast<ARacingGameGameModeBase>(detectedGameMode);
	}

	Spline = GameMode->Spline;
	ensureAlways(Spline);
	// ...
	
}


// Called every frame
void UACO_Position::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	float TargetAcceptanceRadius = GameMode->ArrayOfWaypoints[CurrentWaypoint].TargetReachedRadius;
	float SteeringRadius = GameMode->ArrayOfWaypoints[CurrentWaypoint].SteeringDetectionRadius;
	float distance = FVector::Distance(Owner->GetActorLocation(), GameMode->ArrayOfWaypoints[CurrentWaypoint].WorldPosition);
	//Check if target was reached (overlap)

	if (distance < TargetAcceptanceRadius)
	{
		CurrentWaypoint++;
		if (CurrentWaypoint == GameMode->ArrayOfWaypoints.Num())
		{
			CurrentWaypoint = 0;
		}
	}
	PositionStats.DistanceAlongTrack = GetApproxDistanceClosestToWorldLocation(Owner->GetActorLocation(), Spline);	
	// ...
}

FVector UACO_Position::GetRespawnPoint()
{
	class AAICustomCar_Controller* localAIController = Cast<AAICustomCar_Controller>(Owner->GetController());
	FVector Respawn;

	if (localAIController->IsValidLowLevel())
	{
		int waypointId = localAIController->CurrentWaypoint_id - 1;
		if (waypointId < 1)
			Respawn = GameMode->ArrayOfWaypoints[GameMode->ArrayOfWaypoints.Num() - 1].WorldPosition + FVector(0, 0, 100);
		else
			Respawn = GameMode->ArrayOfWaypoints[localAIController->CurrentWaypoint_id - 1].WorldPosition + FVector(0, 0, 100);
	}
	
	else
	{
		if (CurrentWaypoint < 1)
			Respawn = GameMode->ArrayOfWaypoints[GameMode->ArrayOfWaypoints.Num() - 1].WorldPosition + FVector(0, 0, 100);
		else
			Respawn = GameMode->ArrayOfWaypoints[CurrentWaypoint - 1].WorldPosition + FVector(0, 0, 100);
	}
	
	ensureAlways(Respawn.Size() > 0);
	return Respawn;
}

//adapted from Daniel Krakowiak at https://forums.unrealengine.com/unreal-engine/feedback-for-epic/97850-get-distance-at-location-along-spline
float UACO_Position::GetApproxDistanceClosestToWorldLocation(FVector Pos_WS, const USplineComponent* Spline)
{
	const auto TargetInputKey = Spline->FindInputKeyClosestToWorldLocation(Pos_WS);
	const auto PointIdx = static_cast<int32>(TargetInputKey);

	auto LowDistBound_cm = Spline->GetDistanceAlongSplineAtSplinePoint(PointIdx);
	auto HighDistBound_cm = Spline->GetDistanceAlongSplineAtSplinePoint(PointIdx + 1);
	auto MiddleDistEstimate_cm = (LowDistBound_cm + HighDistBound_cm) * 0.5f;

	const auto& DistanceToInputMapping = Spline->SplineCurves.ReparamTable;

	for (auto IterCount = 0; IterCount < 10; ++IterCount)
	{
		const auto MiddleInputKey = DistanceToInputMapping.Eval(MiddleDistEstimate_cm);

		if (TargetInputKey < MiddleInputKey) {
			HighDistBound_cm = MiddleDistEstimate_cm;
		}
		else {
			LowDistBound_cm = MiddleDistEstimate_cm;
		}

		MiddleDistEstimate_cm = (LowDistBound_cm + HighDistBound_cm) * 0.5f;
	}

	return MiddleDistEstimate_cm;
}





