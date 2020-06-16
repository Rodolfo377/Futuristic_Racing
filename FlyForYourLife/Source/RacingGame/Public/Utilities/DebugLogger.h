// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define printOnScreen(text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, text);

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"
#include "DebugLogger.generated.h"

UCLASS()
class RACINGGAME_API ADebugLogger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADebugLogger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
