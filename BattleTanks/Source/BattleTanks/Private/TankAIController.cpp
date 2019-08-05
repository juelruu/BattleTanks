#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();
	if (PlayerTank)
		UE_LOG(LogTemp, Warning, TEXT("ATankAIController found player %s."), *PlayerTank->GetName())
	else
		UE_LOG(LogTemp, Error, TEXT("ATankAIController can't find player."));
}


ATank* ATankAIController::GetControlledPawn() const {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { 
		UE_LOG(LogTemp, Error, TEXT("Nullptr GetPlayerTank")); 
		return nullptr; 
	}

	return Cast<ATank>(PlayerPawn);
}
