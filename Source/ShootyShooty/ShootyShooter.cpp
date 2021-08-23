// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootyShooter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "ShootyShootyGameModeBase.h"

// Sets default values
AShootyShooter::AShootyShooter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShootyShooter::BeginPlay()
{
	Super::BeginPlay();
	//Hides gun in skeletal mesh
	GetMesh()->HideBoneByName(TEXT("weapon_r"),EPhysBodyOp::PBO_None);
	//Spawns Gun Actor
	Gun=GetWorld()->SpawnActor<AGun>(GunClass);
	//Attaches gun to player
	Gun->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("WeaponAttachPoint"));
	//Set's gun's owner as player (self)
	Gun->SetOwner(this);
	Health=MaxHealth;

}

// Called every frame
void AShootyShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShootyShooter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,&AShootyShooter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"),this,&AShootyShooter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"),this,&AShootyShooter::LookLeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"),this,&AShootyShooter::LookUpDown);
	PlayerInputComponent->BindAction(TEXT("Jump"),EInputEvent::IE_Pressed,this,&AShootyShooter::ShooterJump);
	PlayerInputComponent->BindAction(TEXT("PullTrigger"),EInputEvent::IE_Pressed,this,&AShootyShooter::PullTrigger);



}

//Move forward and backward function
void AShootyShooter::MoveForward(float AxisValue) 
{
	AddMovementInput(GetActorForwardVector()*AxisValue);
}

//Move right and left
void AShootyShooter::MoveRight(float AxisValue) 
{
	AddMovementInput(GetActorRightVector()*AxisValue);
}

//Look up and down
void AShootyShooter::LookUpDown(float AxisValue) 
{
	AddControllerPitchInput(AxisValue);
}

//Look left and right
void AShootyShooter::LookLeftRight(float AxisValue) 
{
AddControllerYawInput(AxisValue);
}

//Jump
void AShootyShooter::ShooterJump() 
{
	ACharacter::Jump();
}

//Tells the gun to shoot
void AShootyShooter::PullTrigger() 
{
   //UE_LOG(LogTemp,Warning,TEXT("Triggered"));
   Gun->Shoot();
}


//Calculates damage
float AShootyShooter::TakeDamage(float DamageAmount,struct FDamageEvent const & DamageEvent,class AController * EventInstigator,AActor * DamageCauser) 
{
	//Calls parent class non overrided function first
	float DamageApplied=Super::TakeDamage(DamageAmount,DamageEvent,EventInstigator,DamageCauser);
	//Heath reduces by damage applied
	Health-=DamageApplied;
	//Health of player is clamped between minimum and maximum health
	Health=FMath::Clamp(Health,MinimumHealth,MaxHealth);
	//Calls IsPlayerDead function to check player status
	if(IsPlayerDead())
	{
		//Gets pointer to gamemode that game is currently runnning in
		AShootyShootyGameModeBase* GameModePointer=GetWorld()->GetAuthGameMode<AShootyShootyGameModeBase>();
		//Calls PawnKilled() function on game mode to notify game that pawn has been killed
		if(GameModePointer!=nullptr)
		{
			GameModePointer->PawnKilled(this);
		}
		//Detaches from controller so that player input is disabled
		DetachFromControllerPendingDestroy();
		//Disables collision
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
		
	}
    return DamageApplied;
}

bool AShootyShooter::IsPlayerDead() const
{
	if(Health<=0){
		
		return true;
	}
	else{
		return false;
	}
}

float AShootyShooter::GetHealth() const
{
	return Health;
}




