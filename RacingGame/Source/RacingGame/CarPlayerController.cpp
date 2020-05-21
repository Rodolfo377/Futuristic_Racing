// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomCar.h"
#include "CarPlayerController.h"

ACustomCar* ACarPlayerController::GetControlledCar() const
{
	return Cast<ACustomCar>(GetPawn());
}