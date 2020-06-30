// Fill out your copyright notice in the Description page of Project Settings.


#include "ACO_HUD.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "../../Public/Pawns/CustomCar.h"
#include "../../Public/Controllers/CarPlayerController.h"
// Sets default values for this component's properties
UACO_HUD::UACO_HUD()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}

void UACO_HUD::Init()
{
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), InterestTag, InterestPoints);
	if (InterestPoints.Num() == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString(TEXT("No interest points in game!")), true);
	}
	else
	{
		FString DebugMsg = FString::Printf(TEXT("%s interest points found in game"), *FString::FromInt(InterestPoints.Num()));
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, DebugMsg, true);
	}
	// ...

	Owner = Cast<ACustomCar>(GetOwner());
	ensureAlways(Owner);
	Controller = Cast<ACarPlayerController>(Owner->GetController());
	ensureAlways(Controller);
}

void UACO_HUD::Update()
{
	FString DebugMsg = FString::Printf(TEXT("%s interest points found in game"), *FString::FromInt(InterestPoints.Num()));
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, DebugMsg, true);

	FVector2D screenPos;
	int screenResX = 0, screenResY = 0;
	Controller->GetViewportSize(screenResX, screenResY);

	DebugMsg = FString::Printf(TEXT("(%s,%s) = screen resolution"),
		*FString::FromInt(screenResX),
		*FString::FromInt(screenResY));

	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, DebugMsg, true);

	for (int i = 0; i < InterestPoints.Num(); i++)
	{
		if (UGameplayStatics::ProjectWorldToScreen(Cast<APlayerController>(Owner->GetController()),
			InterestPoints[i]->GetActorLocation(),
			screenPos,
			false))
		{
			if (screenPos.X < 0 || screenPos.X > screenResX)
			{
				return;
			}
			DebugMsg = FString::Printf(TEXT("(%s,%s) = interest points found in game"), *FString::FromInt(screenPos.X), *FString::FromInt(screenPos.X));
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, DebugMsg, true);
		}
	}
}


