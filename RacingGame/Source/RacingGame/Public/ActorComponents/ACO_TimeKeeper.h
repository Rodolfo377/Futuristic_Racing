// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ACO_TimeKeeper.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RACINGGAME_API UACO_TimeKeeper : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACO_TimeKeeper();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

/*struct LapTimes
{
	std::vector<float> waypointTimes;
};

struct RaceTimes
{
	std::vector<LapTimes> LapTimes;
	std::vector<float> totalLapTimes;
};

struct Timer
{
	float startTime = 0;
	float currentTime = 0;
	void Start();
	void Update();
	void Stop();
};
/**
 * Class for keeping timers within the race - Usable by different game modes
 
class RACINGGAME_API TimeKeeping
{
public:
	TimeKeeping();
	~TimeKeeping();

	//virtual void TickComponent(float DeltaTime) override;

}; */