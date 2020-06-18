// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RacingGameGameModeBase.h"
#include "TimeTrialMode.generated.h"
/**
 * 
 */
UCLASS()
class RACINGGAME_API ATimeTrialMode : public ARacingGameGameModeBase
{
	GENERATED_BODY()
		//member functions
public:
	
	TArray<int> lapTimeRanking;
	void SetActive(bool flag) { IsActive = flag; }
	bool GetActive() { return IsActive; }
	 
	//member variables
protected:
	bool IsActive = false;
	
};
