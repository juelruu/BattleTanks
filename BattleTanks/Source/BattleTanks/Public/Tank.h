#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankAimingComponent;
class UTankMovementComponent;
class AProjectile;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDeligate);
UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 StartingHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = "Setup")
		int32 CurrentHealth = StartingHealth;

public:

	FTankDeligate OnDeath;
	
	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealthInProcent();
	// Sets default values for this pawn's properties

	UPROPERTY(EditAnywhere, Category = "Firing")
		float LaunchSpeed = 200000;

	UPROPERTY(EditAnywhere, Category = "Firing")
		TSubclassOf<AProjectile> ProjectileClass;

	UTankBarrel* Barrel = nullptr;

	float TimeForReloadInSeconds = 3.0;

	double LastReload = 0;

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
		UTankMovementComponent* TankMovementComponent = nullptr;

public:	

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	ATank();

	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void SetBarrelReference(UTankBarrel* SetToBarrel);
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void SetTurretReference(UTankTurret* SetToTurret);
};
