// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShootyShooter.h"


void AShooterAIController::BeginPlay() 
{
    Super::BeginPlay();
    //Gets Player pointer
    PlayerPointer=UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    //Gets Pawn pointer controlled by AI
    SelfPawn=GetPawn();
    //Checks Validity of BT pointer
    if(AIBehaviorTree!=nullptr)
    {
       RunBehaviorTree(AIBehaviorTree);
       //Sets AI and player StartLocation
       GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"),SelfPawn->GetActorLocation());
    }
}

void AShooterAIController::Tick(float DeltaSeconds) 
{
    
    Super::Tick(DeltaSeconds);
}

bool AShooterAIController::IsDead() 
{
    AShootyShooter* ShooterPtr=Cast<AShootyShooter>(GetPawn());
    if(ShooterPtr!=nullptr)
    {
        return ShooterPtr->IsPlayerDead();
    }
    return true;
}
 