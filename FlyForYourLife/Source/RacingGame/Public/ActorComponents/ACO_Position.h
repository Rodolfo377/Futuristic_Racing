// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ACO_Position.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RACINGGAME_API UACO_Position : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACO_Position();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	FVector GetRespawnPoint();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	class ACustomCar* Owner = nullptr;
	FName TrackTag = "Track";
	AActor* Track = nullptr;
	class USplineComponent* Spline = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentWaypoint = 1;
private:
	class ARacingGameGameModeBase* GameMode = nullptr;
};
