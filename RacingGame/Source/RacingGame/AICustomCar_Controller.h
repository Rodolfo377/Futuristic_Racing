// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CustomCar.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "AICustomCar_Controller.generated.h"

/**
 * 
 */
UCLASS()
class RACINGGAME_API AAICustomCar_Controller : public AAIController
{
	GENERATED_BODY()

private:
	ACustomCar* GetControlledCar() const;

	void BeginPlay() override;
	
};
