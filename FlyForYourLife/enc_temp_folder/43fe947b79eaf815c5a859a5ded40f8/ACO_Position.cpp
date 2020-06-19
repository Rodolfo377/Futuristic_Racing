// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/ActorComponents/ACO_Position.h"
#include "../../Public/Pawns/CustomCar.h"
#include "../../Public/GameModes/RacingGameGameModeBase.h"
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
	TArray<AActor*> AllActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TrackTag, AllActors);
	ensureAlways(AllActors.Num() == 1);
	Track = AllActors[0];
	Spline = Cast<USplineComponent>(Track->GetComponentByClass(USplineComponent::StaticClass()));
	ensureAlways(Spline);

	if (UGameplayStatics::GetGameMode(GetWorld()))
	{
		AGameModeBase* detectedGameMode = UGameplayStatics::GetGameMode(GetWorld());
		GameMode = Cast<ARacingGameGameModeBase>(detectedGameMode);
	}

	
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
	/*if (distance < SteeringRadius && distance > TargetAcceptanceRadius)
	{
		Owner->CarEngine->Accelerate(0.05f);
		//printOnScreen("Braking");

	}*/
	if (distance < TargetAcceptanceRadius)
	{
		CurrentWaypoint++;
		if (CurrentWaypoint == GameMode->ArrayOfWaypoints.Num())
		{
			CurrentWaypoint = 1;
		}
		//printOnScreen("Reached Target");
	}
	// ...
}

FVector UACO_Position::GetRespawnPoint()
{
	FVector Respawn = GameMode->ArrayOfWaypoints[CurrentWaypoint].WorldPosition + FVector(0,0,100);
	return Respawn;
}


