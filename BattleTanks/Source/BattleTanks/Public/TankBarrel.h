#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegPerSec = 5.f;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevationDeg = 30.f;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevationDeg = 0.f;

};
