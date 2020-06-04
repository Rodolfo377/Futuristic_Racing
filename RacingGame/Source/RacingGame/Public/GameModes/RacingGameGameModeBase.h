// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RacingGameGameModeBase.generated.h"

class URaceInfo;
/**
 * 
 */
UCLASS()
class RACINGGAME_API ARacingGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	

	virtual void StartMode() {};
	virtual void PauseMode() {};
	virtual void QuitMode() {};
	virtual void CompleteMode() {};

	void setBestLapTime(float t) { bestLapTime = t; }

public:
	//UPROPERTY(EditAnywhere)
	//URaceInfo *RaceInfo = nullptr;
private:
	//TODO: initialize this to be a level-based best Lap Time. 
	float bestLapTime = 0;
	

};
