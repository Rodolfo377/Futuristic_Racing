// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/Utilities/DebugLogger.h"

// Sets default values
ADebugLogger::ADebugLogger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADebugLogger::BeginPlay()
{
	Super::BeginPlay();

	printOnScreen("Hello! Debug Logger here");
	
}

// Called every frame
void ADebugLogger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

