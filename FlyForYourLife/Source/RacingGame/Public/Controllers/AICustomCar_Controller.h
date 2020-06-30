// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Pawns/CustomCar.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "AICustomCar_Controller.generated.h"

class UWorld;
class UACO_CarEngine;
/**
 * 
 */
UCLASS()
class RACINGGAME_API AAICustomCar_Controller : public AAIController
{
	GENERATED_BODY()

	//Member Functions
public:
	AAICustomCar_Controller();

	void Init();
	void Update();

private:
	ACustomCar* ControlledCar = nullptr;
	ACustomCar* GetControlledCar();
	void MoveToTarget(FVector pos);
	
	//Member Variables
public:
	UPROPERTY(EditAnywhere, Category = "Debug Drawing")
	bool PathFollowingDebugDraw = false;
	int CurrentWaypoint_id = 1;
private:	
	class ARacingGameGameModeBase* GameMode = nullptr;
};
