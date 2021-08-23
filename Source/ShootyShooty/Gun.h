// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"


UCLASS()
class SHOOTYSHOOTY_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	USkeletalMesh* GunMesh;
	void Shoot();


private:
	//Root component pointer
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	//Skeletal Mesh Pointer
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;
    //Gun Damage 
	UPROPERTY(EditDefaultsOnly)
	float Damage=20.f;
	//Muzzle Flash particle
	UPROPERTY(EditAnywhere)
	UParticleSystem* GunEmitter;
	//Bullet mark emitter
	UPROPERTY(EditAnywhere)
	UParticleSystem* BulletMarkEmitter;
	//Range of Gun
	UPROPERTY(EditDefaultsOnly)
	float Range=2000.f;
	//Actor who gets damaged by line trace
	AActor* HitActor;
	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;
	UPROPERTY(EditAnywhere)
	USoundBase* ImpactSound;

	
	
	
private:
	FRotator ViewpointRot;
	FVector ViewpointLoc;
	FVector LineTraceEnd ;
	FVector ShotDirection;
	bool LineTraceGun(FHitResult &BulletHitResult);
	//Owner I.E.Shooter character pointer (not casted into BP_ShootyShooter)
	APawn* OwnerPawn=nullptr;
	//Player Controller
	AController* OwnerController=nullptr;
	void SetOwnerController();

};
