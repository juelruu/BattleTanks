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
	PrimaryComponentTick.bCanEverTick = false;

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
	
	if (!ensure(Barrel)) { return; }

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
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* SetToBarrel)
{
	if (!ensure(SetToBarrel)) { return; }
	Barrel = SetToBarrel;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* SetToTurret)
{
	if (!ensure(SetToTurret)) { return; }
	Turret = SetToTurret;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//FRotator TurretRotation = Turret->GetComponentRotation();
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();

	float DeltaRotation = 0;
	float DeltaElevation = AimAsRotator.Pitch - BarrelRotator.Pitch;

	/*if (AimAsRotator.Yaw > 0 ) 
		DeltaRotation = AimAsRotator.Yaw - BarrelRotator.Yaw;
	else*/
	DeltaRotation = AimAsRotator.Yaw - BarrelRotator.Yaw;


	//UE_LOG(LogTemp, Warning, TEXT("Delta: %f - %f = %f"), AimAsRotator.Yaw, BarrelRotator.Yaw, DeltaRotation);
	//UE_LOG(LogTemp, Warning, TEXT("TurretPos: %f %f %f"), AimAsRotator.Yaw, BarrelRotator.Yaw, DeltaRotation);

	Barrel->Elevate(DeltaElevation);
	Turret->Rotate(DeltaRotation);
}
