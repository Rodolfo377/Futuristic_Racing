// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <vector>
#include "../../Public/Utilities/DebugLogger.h"
#include "ACO_TimeKeeper.generated.h"

class ACustomCar;
//Detailed Lap-Record, for waypoint-time comparison
struct LapRecord
{
	float firstWaypointTime = 0;
	float lastWaypointTime = 0;
	std::vector<float> waypointTimes;
};

struct RaceTimes
{
	std::vector<LapRecord> LapTimes;
	std::vector<float> totalLapTimes;
};


struct UTimer
{
	RaceTimes raceClock;
	float startTime = 0;
	float currentTime = 0;
	float lastLapTime = 0;

	void Start(float CurrentWorldTime);
	void Update(float DeltaTime);
	void Stop(float FinalTime);
};



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RACINGGAME_API UACO_TimeKeeper : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACO_TimeKeeper();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly)*/
		//Updates array of checkpoints completed when a custom car object overlaps with a checkpoint object. 
	//FIFO container.
	//@ id: unique id of checkpoint [1,3]
	void UpdateCheckpoint(uint32 checkpointId);

	void StopLapTime();
	void StartLapTime();
	void StopRaceTime();

	UFUNCTION(BlueprintCallable)
	float GetLastLapTime();

	UFUNCTION(BlueprintCallable)
	TArray<float> GetAllLapTimes();

	UFUNCTION(BlueprintCallable)
	int GetCurrentLapID() { return CurrentLap; }

	UFUNCTION(BlueprintCallable)
	float GetCurrentLapTime();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	std::vector<int> Checkpoints = { 0, 0, 0 };
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay")
		int CurrentLap = 1;
public:	
	UTimer RaceTimer;
	ACustomCar *Owner = nullptr;

};