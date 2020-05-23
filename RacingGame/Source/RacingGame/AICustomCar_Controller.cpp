// Fill out your copyright notice in the Description page of Project Settings.


#include "AICustomCar_Controller.h"
#include "Engine/World.h"

void AAICustomCar_Controller::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AIController"));

	ACustomCar* ControlledCar = nullptr;
	ControlledCar = GetControlledCar();

	if (!ControlledCar)
	{
		UE_LOG(LogTemp, Warning, TEXT("Car Pawn not possessed!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("possessed pawn name: %s"), *ControlledCar->GetName());
	}
}

ACustomCar* AAICustomCar_Controller::GetControlledCar() const
{
	return Cast<ACustomCar>(GetWorld()->GetFirstPlayerController());
}