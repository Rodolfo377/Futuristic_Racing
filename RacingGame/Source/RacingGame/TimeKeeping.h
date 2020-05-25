// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <vector>

struct LapTimes
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
 */
class RACINGGAME_API TimeKeeping : public Actor
{
public:
	TimeKeeping();
	~TimeKeeping();

	virtual void Tick(float DeltaTime) override;

};
