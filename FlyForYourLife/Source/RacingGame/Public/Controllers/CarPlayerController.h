// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Pawns/CustomCar.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Delegates/Delegate.h"
#include "CarPlayerController.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerFinishedRace);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerCompletedLap);

UCLASS()
class RACINGGAME_API ACarPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACustomCar* GetControlledCar() const;

	void Init();
	void Update();	
	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
		FPlayerFinishedRace PlayerFinishedRace;
	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
		FPlayerFinishedRace PlayerCompletedLap;
private:
	class ACustomCar* ControlledCar = nullptr;
};
