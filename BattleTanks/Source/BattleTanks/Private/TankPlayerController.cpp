#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "BattleTanks.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto AimingComponent = GetControlledPawn()->FindComponentByClass<UTankAimingComponent>();

	if (AimingComponent) {
		FoundAimingComponent(AimingComponent);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player controller can't find aiming component at BeginPlay"));
	}
}


ATank* ATankPlayerController::GetControlledPawn() const {
	return Cast<ATank>(GetPawn());
}

/*void ATankPlayerController::FoundAimingComponent(UTankAimingComponent* AimCompRef) {

}*/

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() {

	if (!ensure(GetControlledPawn())) { return; }

	FVector HitLocation{2.0};

	if (GetSightRayHitLocation(HitLocation)) {
		GetControlledPawn()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OurHitLocation) const {
	int32 ViewportXSize, ViewportYSize;
	FVector CameraWorldDirection;
	FVector LookDirection;

	GetViewportSize(ViewportXSize, ViewportYSize);
	auto ScreenLocation = FVector2D(ViewportXSize * ViewportXlocation, ViewportYSize * ViewportYLocation);

	if (GetLookDirection(ScreenLocation, LookDirection))
		GetLookVectorHitLocation(LookDirection, OurHitLocation);

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const{
	FVector CameraWorldDirection;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldDirection,
		LookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
	FHitResult HitResult;

	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if(GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility)){
		HitLocation = HitResult.Location;
		return true;
	}
	else {
		HitLocation = FVector(0);
		return false;
	}
}