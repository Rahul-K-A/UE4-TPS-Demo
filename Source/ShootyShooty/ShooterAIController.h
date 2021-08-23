// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTYSHOOTY_API AShooterAIController : public AAIController
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaSeconds) override;
	bool IsDead();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
    //Pointer to player pawn
    APawn* PlayerPointer;
	//Pointer to pawn controlled by AI
	APawn* SelfPawn;
	//How close AI can get to player 
	float AcceptanceRadius=200.f;
	//Pointer to required behaviour tree
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehaviorTree; 

	
};
