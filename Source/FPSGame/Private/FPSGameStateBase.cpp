// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGameStateBase.h"
#include "SurfaceIterators.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "FPSPlayerController.h"


void AFPSGameStateBase::MulticastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool bMissionSuccess, bool bIsCarryingObjective)
{

	for(FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		AFPSPlayerController* PC = Cast<AFPSPlayerController>(It->Get());

		if (PC && PC->IsLocalController())
		{
			PC->OnMissionComplete(InstigatorPawn, bMissionSuccess, bIsCarryingObjective);

			APawn* MyPawn = PC->GetPawn();
			if (MyPawn)
			{
				MyPawn->DisableInput(PC);
			}
		}
	}
}
