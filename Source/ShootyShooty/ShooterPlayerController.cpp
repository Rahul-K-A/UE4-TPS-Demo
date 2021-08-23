// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"




void AShooterPlayerController::BeginPlay() 
{
     Super::BeginPlay();
     HUDWidget=CreateWidget(this,HUDClass);
     if( HUDWidget!=nullptr)
     {
         HUDWidget->AddToViewport();
     }    
}


//Called by game mode to n=take care of post pawn death actions like rendering death screen
void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner) 
{
    Super::GameHasEnded(EndGameFocus,bIsWinner);
    if(bIsWinner)    //If player has won
    {
        UUserWidget* WinScreenWidget= CreateWidget(this,WinScreenClass);
        if(WinScreenWidget!=nullptr)
        {
         HUDWidget->RemoveFromViewport();
         WinScreenWidget->AddToViewport();
        }
    }
    else                 //If player has lost
    {
        UUserWidget* LoseScreenWidget= CreateWidget(this,LoseScreenClass);
        if(LoseScreenWidget!=nullptr)
        {
         HUDWidget->RemoveFromViewport();
         LoseScreenWidget->AddToViewport();
        }

    }
    GetWorldTimerManager().SetTimer(RestartTimer,this,&APlayerController::RestartLevel,TimerDelay);
}

