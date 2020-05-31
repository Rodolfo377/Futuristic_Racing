// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/ActorComponents/ACO_TimeKeeper.h"
#include "Engine/World.h"
#include "Internationalization/Text.h"
// Sets default values for this component's properties
UACO_TimeKeeper::UACO_TimeKeeper()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UACO_TimeKeeper::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	
}


// Called every frame
void UACO_TimeKeeper::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//RaceTimer.Update(DeltaTime);
	// ...
}

void UACO_TimeKeeper::StopLapTime()
{
	float CurrentTime = GetWorld()->TimeSeconds;
	RaceTimer.Stop(CurrentTime);
	
}

void UACO_TimeKeeper::StartLapTime()
{
	float CurrentTime = GetWorld()->TimeSeconds;
	RaceTimer.Start(CurrentTime);
}

void UACO_TimeKeeper::StopRaceTime()
{
}

float UACO_TimeKeeper::GetLastLapTime()
{
	return RaceTimer.lastLapTime;
}

TArray<float> UACO_TimeKeeper::GetAllLapTimes()
{
	TArray<float> lapTimes;
	int x = 3;
	lapTimes.Init(0, x);

	for (int i = 0; i < RaceTimer.raceClock.totalLapTimes.size(); i++)
	{
		lapTimes[i] = RaceTimer.raceClock.totalLapTimes[i];
	}

	return lapTimes;
}

void UTimer::Start(float CurrentWorldTime)
{
	startTime = CurrentWorldTime;
	LapTimes lap;	
	lap.waypointTimes.push_back(startTime);
	lap.firstWaypointTime = startTime;
	raceClock.LapTimes.push_back(lap);
	printOnScreen("Start Lap Timer!");
}

void UTimer::Update(float DeltaTime)
{
}


void UTimer::Stop(float FinalTime)
{
	int index = raceClock.LapTimes.size() - 1;
	raceClock.LapTimes[index].waypointTimes.push_back(FinalTime);
	raceClock.LapTimes[index].lastWaypointTime = FinalTime;
	float lapTime = raceClock.LapTimes[index].lastWaypointTime
		- raceClock.LapTimes[index].firstWaypointTime;
	raceClock.totalLapTimes.push_back(lapTime);
	lastLapTime = lapTime;
	FString lapResult = "Stop Lap Timer : " + FString::SanitizeFloat(lapTime);
	printOnScreen(lapResult);

	
}
