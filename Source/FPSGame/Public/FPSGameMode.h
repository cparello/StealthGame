// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"

UCLASS()
class AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AFPSGameMode();

	void CompletedMission(APawn* InstigatorPawn);

	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void OnMissionCompleted(APawn* InstigatorPawn);


	void ObjectiveMissing(APawn* InstigatorPawn);

	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void OnObjectiveMissing(APawn* InstigatorPawn);

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Spectating")
	TSubclassOf<AActor> SpectatingViewpointClass;

};



