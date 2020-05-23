// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CustomCar.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CarPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RACINGGAME_API ACarPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACustomCar* GetControlledCar() const;

	void BeginPlay() override;
	
};
