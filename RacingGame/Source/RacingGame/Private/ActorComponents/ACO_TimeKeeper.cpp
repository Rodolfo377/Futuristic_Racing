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
	RaceTimer.Start(GetWorld()->TimeSeconds);
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
	RaceTimer.Stop(GetWorld()->TimeSeconds);
}

void UACO_TimeKeeper::StopRaceTime()
{
}

void Timer::Start(float CurrentWorldTime)
{
	startTime = CurrentWorldTime;
	LapTimes lap;
	raceClock.LapTimes.push_back(lap);
	lap.waypointTimes.push_back(startTime);
	lap.firstWaypointTime = startTime;
	printOnScreen("Start Race!");
}

void Timer::Update(float DeltaTime)
{
}

void Timer::Stop(float FinalTime)
{
	raceClock.LapTimes[raceClock.LapTimes.size() - 1].waypointTimes.push_back(FinalTime);
	raceClock.LapTimes[raceClock.LapTimes.size() - 1].lastWaypointTime = FinalTime;
	float lapTime = raceClock.LapTimes[raceClock.LapTimes.size() - 1].lastWaypointTime
		- raceClock.LapTimes[raceClock.LapTimes.size() - 1].firstWaypointTime;
	FString lapResult = "Stop Lap Timer : " + FString::SanitizeFloat(lapTime);
	printOnScreen(lapResult);
}
