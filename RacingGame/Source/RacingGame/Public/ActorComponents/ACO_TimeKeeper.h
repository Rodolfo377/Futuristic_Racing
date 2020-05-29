// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <vector>
#include "../../Public/Utilities/DebugLogger.h"
#include "ACO_TimeKeeper.generated.h"

struct LapTimes
{
	float firstWaypointTime = 0;
	float lastWaypointTime = 0;
	std::vector<float> waypointTimes;
};

struct RaceTimes
{
	std::vector<LapTimes> LapTimes;
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
	UTimer RaceTimer;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	
	void StopLapTime();
	void StopRaceTime();
	UFUNCTION(BlueprintCallable)
	float GetLastLapTime();

	UFUNCTION(BlueprintCallable)
	TArray<float> GetAllLapTimes();
};
