// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "FPSGameStateBase.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();

	GameStateClass = AFPSGameStateBase::StaticClass();
}

void AFPSGameMode::CompletedMission(APawn* InstigatorPawn, bool bMissionSuccess, bool bIsCarryingObjective)
{
	if(InstigatorPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("InstigatorPawn"))

		if(SpectatingViewpointClass)
		{
			UE_LOG(LogTemp, Warning, TEXT("SpectatingViewpointClass"))
			TArray<AActor*> ReturnedActors;

			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnedActors);

			/*AActor* NewViewTarget = nullptr;*/
			if (ReturnedActors.Num() > 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("ReturnedActors.Num() > 0"))
				AActor* NewViewTarget = ReturnedActors[0];

				for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
				{
					APlayerController* PC = It->Get();
					if(PC)
					{
						PC->SetViewTargetWithBlend(NewViewTarget, 0.5f, VTBlend_Cubic);
					}
				}
			}
		}else
		{
			UE_LOG(LogTemp, Warning, TEXT("spectatng viewpoint class is null"))
		}
		
	}

	AFPSGameStateBase* GS = GetGameState<AFPSGameStateBase>();
	if(GS)
	{
		GS->MulticastOnMissionComplete(InstigatorPawn, bMissionSuccess, bIsCarryingObjective);
	}

	OnMissionCompleted(InstigatorPawn, bMissionSuccess, bIsCarryingObjective);
}
