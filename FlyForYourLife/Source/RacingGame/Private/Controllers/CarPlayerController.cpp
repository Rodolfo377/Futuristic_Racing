// Fill out your copyright notice in the Description page of Project Settings.

#include "../../Public/Controllers/CarPlayerController.h"
#include "../../Public/Pawns/CustomCar.h"

void ACarPlayerController::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("PlayerController"));

	ControlledCar = GetControlledCar();
	ensureAlways(ControlledCar);

	ControlledCar->Init();
}

void ACarPlayerController::Update()
{
	ControlledCar->Update();
}

ACustomCar* ACarPlayerController::GetControlledCar() const
{
	return Cast<ACustomCar>(GetPawn());
}