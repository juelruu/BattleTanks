#include "TankBarrel.h"
#include "CoreMinimal.h"

void UTankBarrel::Elevate(float RelativeSpeed) {

	auto Speed = FMath::Clamp<float>(RelativeSpeed, -1, +1);

	auto ElevationChange = Speed * MaxDegPerSec * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDeg, MaxElevationDeg);

	SetRelativeRotation(FRotator(Elevation, 0, 0));
}