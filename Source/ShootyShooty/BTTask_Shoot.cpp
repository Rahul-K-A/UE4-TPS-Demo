// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "ShootyShooter.h"
#include "AIController.h"


UBTTask_Shoot::UBTTask_Shoot() 
{
    NodeName="Shoot";
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
    Super::ExecuteTask(OwnerComp,NodeMemory);
    //ChecksAIController Validity
    if(OwnerComp.GetAIOwner()==nullptr)
    {
        return EBTNodeResult::Failed;
    }
    //Pawn which is going to shoot at player
    APawn* PawnWhichShoots= OwnerComp.GetAIOwner()->GetPawn();
    //Same pawn casted as Shooty Shooter Class
    AShootyShooter* Character = Cast<AShootyShooter>(PawnWhichShoots);
    if (Character == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    Character->PullTrigger();
    return EBTNodeResult::Succeeded;
}
