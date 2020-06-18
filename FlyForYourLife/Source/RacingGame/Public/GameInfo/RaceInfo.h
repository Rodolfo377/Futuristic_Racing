// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "RaceInfo.generated.h"


UENUM(BlueprintType)
enum class EMatchTypeSelection : uint8
{
	NONE,
	RACING_ARCADE,
	RACING_PURE,
	TIME_TRIAL,
	ELIMINATION
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RACINGGAME_API URaceInfo : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URaceInfo();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Laps = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Opponents = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EMatchTypeSelection SelectedMatchType;

		
	void BeginPlay();

	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction);

};



