// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ACO_HUD.generated.h"

//This class is meant to be used by a player car only, as it implements the HUD on screen. 

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RACINGGAME_API UACO_HUD : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACO_HUD();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	
	UPROPERTY(VisibleAnywhere)
	FName InterestTag = "Interest";

	TArray<AActor*> InterestPoints;
	class ACustomCar *Owner = nullptr;
	class ACarPlayerController *Controller = nullptr;
};
