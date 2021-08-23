// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
//#include "Engine/World.h""

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root=CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	Mesh=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::Shoot() 
{
	SetOwnerController();
	FHitResult BulletHitResult;
	//Spawns particle
    UGameplayStatics::SpawnEmitterAttached(GunEmitter,Mesh,TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound,Mesh,TEXT("MuzzleFlashSocket"));
    
    //Line Trace
    bool bHitSuccess=LineTraceGun(BulletHitResult);
	//If Line Trace Successful
    if(bHitSuccess==true)
	{    
		ShotDirection=-ViewpointRot.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),BulletMarkEmitter,BulletHitResult.Location,ShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, BulletHitResult.Location);
		UE_LOG(LogTemp,Warning,TEXT("done sound"));
		HitActor=BulletHitResult.GetActor();

		if(HitActor!=nullptr)
		{
			SetOwnerController();
			//UE_LOG(LogTemp,Warning,TEXT("%s shot %s"),*GetOwner()->GetName(),*HitActor->GetName());
			FPointDamageEvent DamageEvent(Damage,BulletHitResult,ShotDirection,nullptr);
			HitActor->TakeDamage(Damage,DamageEvent,OwnerController,this);
		}
	}
}



bool AGun::LineTraceGun(FHitResult &BulletHitResult) 
{
	 //Get Player camera rotation and position
	if(OwnerController==nullptr)
	{
		UE_LOG(LogTemp,Error,TEXT("WOo["));
		return false;
	}
	OwnerController->GetPlayerViewPoint(ViewpointLoc,ViewpointRot);
	//Get end position vector to line trace to
	LineTraceEnd = ViewpointLoc + ViewpointRot.Vector()*Range;
	//Hit target information holder
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	UE_LOG(LogTemp,Warning,TEXT("Done tracing"));
	return GetWorld()->LineTraceSingleByChannel(BulletHitResult,ViewpointLoc,LineTraceEnd,ECollisionChannel::ECC_GameTraceChannel2,Params);
	
}

void AGun::SetOwnerController() 
{
	OwnerPawn=Cast<APawn>(GetOwner());
	if(OwnerPawn==nullptr)
	{
		UE_LOG(LogTemp,Error,TEXT("No pawn found"));
		OwnerPawn=nullptr;
		OwnerController=nullptr;
		return;
	}
	else
	OwnerController=OwnerPawn->GetController();
	//Validity Check
}

