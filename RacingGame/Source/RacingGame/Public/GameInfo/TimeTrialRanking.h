// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TimeTrialRanking.generated.h"

USTRUCT()
struct FRaceDetails
{
	GENERATED_BODY()

	FRaceDetails() {}
	FRaceDetails(FString a, TArray<float> b, FDateTime c): PlayerName(a), lapTimes(b), PlayerSaveSlotDate(c){}

	UPROPERTY()
	FString PlayerName;

	UPROPERTY()
	TArray<float> lapTimes;

	UPROPERTY()
	FDateTime PlayerSaveSlotDate;
};
/**
 * 
 */
UCLASS()
class RACINGGAME_API UTimeTrialRanking : public USaveGame
{
	GENERATED_BODY()
	//Methods
public:
	UTimeTrialRanking() {}
	//Attempts to add entry to leaderbord
	void AddEntry(FString playerName, TArray<float> laptimes, FDateTime c);
protected:
private:
	//Variables
public:
	//Stores ranking of best lap times of a track
	UPROPERTY()
		TArray<FRaceDetails> BestLapTimes;

};
