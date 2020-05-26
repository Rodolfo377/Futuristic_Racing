// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RacingGameGameModeBase.generated.h"

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

};
