// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::CompletedMission(APawn* InstigatorPawn)
{
	if(InstigatorPawn)
	{
		InstigatorPawn->DisableInput(nullptr);

		if(SpectatingViewpointClass)
		{
			TArray<AActor*> ReturnedActors;

			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnedActors);

			AActor* NewViewTarget = nullptr;
			if (ReturnedActors.Num() > 0)
			{
				AActor* NewViewTarget = ReturnedActors[0];
				APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());

				if (PC)
				{
					PC->SetViewTargetWithBlend(NewViewTarget, 0.5f, VTBlend_Cubic);
				}
			}
		}else
		{
			UE_LOG(LogTemp, Warning, TEXT("spectatng viewpoint class is null"))
		}

		
		
	}
	OnMissionCompleted(InstigatorPawn);	
}

void AFPSGameMode::ObjectiveMissing(APawn* InstigatorPawn)
{
	OnObjectiveMissing(InstigatorPawn);
}

