// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CustomCar.h"
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

	virtual void Tick(float DeltaTime) override;
private:
	ACustomCar* GetControlledCar() const;
	ACustomCar* GetPlayerCar() const;
	void BeginPlay() override;
	
};
