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

	virtual void Tick(float DeltaTime) override;
private:
	ACustomCar* GetControlledCar() const;
	ACustomCar* GetPlayerCar() const;
	void BeginPlay() override;
	void MoveTo(FVector pos);
	
	//Member Variables
public:
	UPROPERTY(EditAnywhere, Category = "Debug Drawing")
	bool PathFollowingDebugDraw = false;

	UPROPERTY(EditAnywhere, Category = "Adjustments")
	float TargetAcceptanceRadius = 200.0f;
private:
	
	int CurrentWaypoint_id = 0;
	class ARacingGameGameModeBase* GameMode;
};
