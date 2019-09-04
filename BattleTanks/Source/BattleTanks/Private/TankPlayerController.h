#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
class UTankAimingComponent;

UCLASS()
class ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:

	float ViewportXlocation = 0.5;
	float ViewportYLocation = 0.333;

	int32 LineTraceRange = 1000000;

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
		ATank* GetControlledPawn() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimCompRef);

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& OurHitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};

