#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
	
	if (!Barrel) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// Calculate vector to target
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity, 
		StartLocation, 
		HitLocation, 
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveAimSolution) {
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("%f No aim"), GetWorld()->GetTimeSeconds());
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* SetToBarrel)
{
	if (!SetToBarrel) { return; }
	Barrel = SetToBarrel;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* SetToTurret)
{
	if (!SetToTurret) { return; }
	Turret = SetToTurret;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	
	auto DeltaRotation = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotation.Pitch);
}
