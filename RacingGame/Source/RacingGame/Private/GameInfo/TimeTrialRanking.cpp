// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\Public\GameInfo\TimeTrialRanking.h"

void UTimeTrialRanking::AddEntry(FString playerName, float lastLapTime, FDateTime c)
{
	//FRaceDetails newEntry(playerName, lastLapTime, c);
	FRaceDetails newEntry;
	newEntry.PlayerName = playerName;
	newEntry.lapTime = lastLapTime;
	newEntry.PlayerSaveSlotDate = c;

	BestLapTimes.Emplace(newEntry);
}

void UTimeTrialRanking::printLapTimes()
{
	for (auto lap : BestLapTimes)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : %f"), *lap.PlayerName, lap.lapTime);
	}
}
