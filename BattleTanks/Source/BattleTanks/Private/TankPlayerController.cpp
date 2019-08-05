// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto ControlledTank = GetControlledPawn();
	if (ControlledTank)
		UE_LOG(LogTemp, Warning, TEXT("ATankPlayerContoller start play by %s."), *ControlledTank->GetName())
	else
		UE_LOG(LogTemp, Error, TEXT("ATankPlayerContoller don't start play."));
}


ATank* ATankPlayerController::GetControlledPawn() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::Tick(float DeltaTime) {

	if (!GetControlledPawn()) { return; }
	FVector HitLocation;

	UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
}