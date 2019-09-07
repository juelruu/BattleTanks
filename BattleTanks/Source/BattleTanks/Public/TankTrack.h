// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
		float MaxDrivingForce = 40000000;
	
private:
	UTankTrack();
	virtual void BeginPlay() override;
	void ApplySidewayForce();
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:

	UFUNCTION(BlueprintCallable, Category = Movement)
		void SetThrottle(float Throttle);

private:	
	void Drive();

	float CurrentThrottle = 0;

};
