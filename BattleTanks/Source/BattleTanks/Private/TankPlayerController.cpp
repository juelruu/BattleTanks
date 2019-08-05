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
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() {

	if (!GetControlledPawn()) { return; }

	FVector HitLocation{2.0};

	GetSightRayHitLocation(HitLocation);
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OurHitLocation) const {
	int32 ViewportXSize, ViewportYSize;

	GetViewportSize(ViewportXSize, ViewportYSize);
	auto ScreenLocation = FVector2D(ViewportXSize * ViewportXlocation, ViewportYSize * ViewportYLocation);
	UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString());
	return true;
}