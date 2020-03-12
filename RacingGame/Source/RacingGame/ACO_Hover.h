// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "ACO_Hover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RACINGGAME_API UACO_Hover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACO_Hover();
	void SetupInputComponent();
	void SetupPhysicsHandle();
	void Accelerate(float value);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	AActor* Owner = nullptr;
	ACharacter* MyCharacter = nullptr;

	UPROPERTY(VisibleAnywhere)
	UInputComponent* InputComponent = nullptr;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
};
