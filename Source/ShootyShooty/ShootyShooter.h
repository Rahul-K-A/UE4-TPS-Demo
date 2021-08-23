// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShootyShooter.generated.h"

class AGun;

UCLASS()
class SHOOTYSHOOTY_API AShootyShooter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShootyShooter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float AxisValue);
    void MoveRight(float AxisValue);
	void LookUpDown(float AxisValue);
	void LookLeftRight(float AxisValue);
    void ShooterJump();
    void PullTrigger();
    virtual float TakeDamage(float DamageAmount,struct FDamageEvent const & DamageEvent,class AController * EventInstigator,AActor * DamageCauser);
	//Returns if player Dead
	UFUNCTION(BlueprintPure)
	bool IsPlayerDead() const;
	UFUNCTION(BlueprintPure)
	float GetHealth() const;
	
private:
//Pointer to se;ect which kind of gun
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;
//Pointer for current gun
	UPROPERTY()
	AGun* Gun;
	//Sets minimum,maximum and current health
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth=150.f;
	float Health;
	float MinimumHealth=0.f;
	
	
};
