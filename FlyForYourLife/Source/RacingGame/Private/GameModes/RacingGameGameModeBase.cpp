// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/GameModes/RacingGameGameModeBase.h"
#include "../../Public/GameInfo/RaceInfo.h"
#include "../../Public/Pawns/CustomCar.h"
#include "../../Public/ActorComponents/ACO_Position.h"

#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SplineComponent.h"

void ARacingGameGameModeBase::BeginPlay()
{
	RaceInfo = Cast<URaceInfo>(GetComponentByClass(URaceInfo::StaticClass()));
	check(RaceInfo);
	TArray<AActor*> AllActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Track"), AllActors);
	ensureAlways(AllActors.Num() == 1);
	Track = AllActors[0];
	Spline = Cast<USplineComponent>(Track->GetComponentByClass(USplineComponent::StaticClass()));
	ensureAlways(Spline);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACustomCar::StaticClass(), AllActors);
	for (AActor* Car: AllActors)
	{
		ACustomCar* vehicle = Cast<ACustomCar>(Car);
		ensureAlways(vehicle);
		AllCars.Emplace(vehicle);
	}
}

void ARacingGameGameModeBase::Tick(float DeltaTime)
{
	SortVehicles(AllCars);
}

void ARacingGameGameModeBase::SortVehicles(TArray<ACustomCar*> AllVehicles)
{
	TArray<ACustomCar*> SortedVehicles = AllVehicles;
	//1 - Sort by vehicle lap # and lap progress
	for (int i = 0; i < SortedVehicles.Num() - 1; i++)
	{
		int max_id = i;
		for (int j = i; j < SortedVehicles.Num(); j++)
		{
			//if CompareCar is at the same lap, but with greater progress
			bool sameLapCondition = SortedVehicles[j]->GetCurrentLap() == SortedVehicles[max_id]->GetCurrentLap()
				&& SortedVehicles[j]->CarPosition->PositionStats.DistanceAlongTrack > SortedVehicles[max_id]->CarPosition->PositionStats.DistanceAlongTrack;
			//if Compare car is at a greater lap than the base car
			bool nextLapCondition = SortedVehicles[j]->GetCurrentLap() > SortedVehicles[max_id]->GetCurrentLap();

			if (sameLapCondition || nextLapCondition)
			{
				Swap(SortedVehicles[i], SortedVehicles[j]);
			}
		}
	}

	//Assign positions
	for (size_t i = 0; i < SortedVehicles.Num(); i++)
	{
		SortedVehicles[i]->CarPosition->PositionStats.RacePosition = i + 1;
	}

	//return SortedVehicles;
}



