// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/Controllers/AICustomCar_Controller.h"
#include "../../Public/ActorComponents/ACO_CarEngine.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"



void AAICustomCar_Controller::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AIController"));

	ACustomCar* PlayerCar = nullptr;
	PlayerCar = GetPlayerCar();

	if (!PlayerCar)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Car not found!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Car found!: name: %s"), *PlayerCar->GetName());
	}
}

void AAICustomCar_Controller::Tick(float DeltaTime)
{
	if (GetControlledCar())
	{
		GetControlledCar()->CarEngine->Accelerate(1.0f);
	}
}

ACustomCar* AAICustomCar_Controller::GetControlledCar() const
{
	return Cast<ACustomCar>(GetPawn());
}

ACustomCar * AAICustomCar_Controller::GetPlayerCar() const
{
	return Cast<ACustomCar>(GetWorld()->GetFirstPlayerController()->GetPawn());
}