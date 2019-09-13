#include "Public/Tank.h"
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastReload) > TimeForReloadInSeconds;
	if (Barrel && isReloaded) {
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastReload = FPlatformTime::Seconds();
	}
}

void ATank::SetBarrelReference(UTankBarrel* SetToBarrel)
{
	TankAimingComponent->SetBarrelReference(SetToBarrel);
	Barrel = SetToBarrel;
}

void ATank::SetTurretReference(UTankTurret* SetToTurret)
{
	TankAimingComponent->SetTurretReference(SetToTurret);
}

// Sets default values
ATank::ATank(){
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay(){
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation) {
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser){

	int32 DamagePoint = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoint, 0, CurrentHealth);

	CurrentHealth -=DamageToApply;
	
	if(CurrentHealth <= 0){
		OnDeath.Broadcast();
	}
	else{
		UE_LOG(LogTemp, Warning, TEXT("%s health: %i DamageAmount: %f, DamageToApply: %i"), *GetName(), CurrentHealth, DamageAmount, DamageToApply);
	}
		
	return DamageToApply;
}

float ATank::GetHealthInProcent(){
	return (float)CurrentHealth / (float)StartingHealth;
}
