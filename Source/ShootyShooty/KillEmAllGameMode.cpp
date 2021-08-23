// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"


void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled) 
{
    Super::PawnKilled(PawnKilled);
    APlayerController* PlayerControllerPointer=Cast<APlayerController>(PawnKilled->GetController());
    if(PlayerControllerPointer!=nullptr)
    {
        EndGame(false);                      //ends game if player has failed. "false" magic number in parameter signifies player has failed to win
    }

//Iterates through all pawns controlled by AI and if the loop finishes.I.E all of em are ead then end game is executed
    for(AShooterAIController* Controller: TActorRange<AShooterAIController>(GetWorld()))
    {
        if(!Controller->IsDead())
        {
            return;
        }
    }
    EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner) 
{
    for(AController* Controller: TActorRange<AController>(GetWorld()))
    {
        bool bIsWinner= Controller->IsPlayerController() == bIsPlayerWinner;            //Basically XNOR Gate whose output is stored inbIs Winner
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);                     //GameHasEnded first param is to focus camera. In this case we want to focus each controller's camera on their respective pawns. bIswinner is discussed aabove. Will be false for player controller if player dies and true for Ai controlled pawn and vice versa
    }
}
