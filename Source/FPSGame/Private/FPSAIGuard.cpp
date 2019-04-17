// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"


// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
	UE_LOG(LogTemp, Warning, TEXT("CONSTRUCTOR"))

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	

}


// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);

	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnNoiseHeard);
	
}

void AFPSAIGuard::ResetOrientation()
{
	SetActorRotation(OriginalRotation);
}

void AFPSAIGuard::OnPawnSeen(APawn* SeenPawn)
{
	UE_LOG(LogTemp, Warning, TEXT("SEEN"))

	if (SeenPawn == nullptr)return;
	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Yellow, false, 10.0f);
}

void AFPSAIGuard::OnNoiseHeard(APawn* PawnInstigator, const FVector & Location, float Volume)
{
	UE_LOG(LogTemp, Warning, TEXT("HEARD"))

	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Red, false, 10.0f);

	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();

	FRotator NewLookAt =  FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAt.Pitch = 0.0f;
	NewLookAt.Roll = 0.0f;

	SetActorRotation(NewLookAt);

	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetOrientation, this, &AFPSAIGuard::ResetOrientation, 3.0f);
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSAIGuard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

