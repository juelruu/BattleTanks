// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:

	float ViewportXlocation = 0.5;
	float ViewportYLocation = 0.333;

	ATank* GetControlledPawn() const;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& OurHitLocation) const;
};

