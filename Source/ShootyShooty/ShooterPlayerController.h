// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
class UUserWidget;
UCLASS()
class SHOOTYSHOOTY_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
	public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;


	private:
	UPROPERTY(EditAnywhere)
	float TimerDelay=5.f;
	FTimerHandle RestartTimer;
	UUserWidget* HUDWidget;



    private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> LoseScreenClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> WinScreenClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> HUDClass;
	
	
	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
	
};
