// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\Public\GameInfo\TimeTrialRanking.h"

void UTimeTrialRanking::AddEntry(FString playerName, TArray<float> laptimes, FDateTime c)
{
	FRaceDetails newEntry(playerName, laptimes, c);
	BestLapTimes.Push(newEntry);
}
