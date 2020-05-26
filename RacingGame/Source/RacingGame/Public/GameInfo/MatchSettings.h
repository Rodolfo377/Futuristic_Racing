// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "MatchSettings.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EMatchTypeSelection: uint8
{
	NONE,
	RACING_ARCADE,
	RACING_PURE,
	TIME_TRIAL,
	ELIMINATION
};

UCLASS()
class RACINGGAME_API AMatchSettings : public AWorldSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Laps = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Opponents = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMatchTypeSelection SelectedMatchType;
};
