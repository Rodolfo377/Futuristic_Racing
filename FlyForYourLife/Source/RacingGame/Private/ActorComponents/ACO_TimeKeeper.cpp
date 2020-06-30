// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/ActorComponents/ACO_TimeKeeper.h"
#include "../../Public/Pawns/CustomCar.h"
#include "../../Public/ActorComponents/ACO_SaveGameData.h"
#include "../../Public/GameModes/TimeTrialMode.h"
#include "../../Public/GameInfo/RaceInfo.h"
#include "../../Public/GameModes/RacingGameGameModeBase.h"
#include "../../Public/Controllers/AICustomCar_Controller.h"

#include "Engine/World.h"
#include "Internationalization/Text.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UACO_TimeKeeper::UACO_TimeKeeper()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


float UACO_TimeKeeper::GetCurrentLapTime()
{
	int index = RaceTimer.raceClock.LapTimes.size()-1;
	if (!RaceTimer.raceClock.LapTimes.empty())
	{
		float lapTime = GetWorld()->TimeSeconds - RaceTimer.raceClock.LapTimes[index].firstWaypointTime;;
		return lapTime;
	}
	return 0;
}

void UACO_TimeKeeper::BeginPlay()
{
	Super::BeginPlay();
	Owner = (ACustomCar*)GetOwner();
	ensureAlways(Owner);
	
	ATimeTrialMode* timeTrialGameMode = nullptr;
	
	



	
	// ...
	
}


// Called every frame
void UACO_TimeKeeper::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!RaceInfo->IsValidLowLevel())
	{
		ARacingGameGameModeBase* GameMode = Cast<ARacingGameGameModeBase>
			(UGameplayStatics::GetGameMode(this));
		if (GameMode->IsValidLowLevel())
		{
			RaceInfo = GameMode->RaceInfo;
			if (RaceInfo->IsValidLowLevel())
			{
				printOnScreen(TEXT("Loaded Race Info"))
			}
			
		}
	}
}

void UACO_TimeKeeper::UpdateCheckpoint(uint32 checkpointId)
{
	if (Checkpoints.size() == 3)
	{
		if (Checkpoints[0] == 0 && Checkpoints[1] == 0 && Checkpoints[2] == 0)
		{
			RaceTimer.Start(GetWorld()->TimeSeconds);
		}

		if ((Checkpoints[0] == 1) && (Checkpoints[1] == 2) && (Checkpoints[2] == 3))
		{
			
			StopLapTime();	
			if (Owner->GetCurrentLap() == RaceInfo->Laps)
			{
				AAICustomCar_Controller* DummyController = NewObject<AAICustomCar_Controller>(AAICustomCar_Controller::StaticClass());
				//Owner->Possess(DummyController);
				DummyController->Possess(Owner);
				
				return;
			}
			StartLapTime();	
			CurrentLap++;
		}

		if (Checkpoints[2] != checkpointId)
		{
			Checkpoints[0] = Checkpoints[1];
			Checkpoints[1] = Checkpoints[2];
			Checkpoints[2] = checkpointId;
		}
	}
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

	for (int i = 0; i < RaceTimer.raceClock.totalLapTimes.size(); i++)
	{
		lapTimes.Emplace(RaceTimer.raceClock.totalLapTimes[i]);
	}

	return lapTimes;
}

void UTimer::Start(float CurrentWorldTime)
{
	startTime = CurrentWorldTime;
	LapRecord lap;	
	lap.waypointTimes.push_back(startTime);
	lap.firstWaypointTime = startTime;
	raceClock.LapTimes.push_back(lap);
	//printOnScreen("Start Lap Timer!");
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
