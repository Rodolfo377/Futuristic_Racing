// Fill out your copyright notice in the Description page of Project Settings.

#include "CarPlayerController.h"
#include "CustomCar.h"

void ACarPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController"));

	ACustomCar* ControlledCar = nullptr;
	ControlledCar = GetControlledCar();

	if (!ControlledCar)
	{
		UE_LOG(LogTemp, Warning, TEXT("Car PAwn not possessed!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("possessed pawn name: %s"), *ControlledCar->GetName());
	}
}

ACustomCar* ACarPlayerController::GetControlledCar() const
{
	return Cast<ACustomCar>(GetPawn());
}