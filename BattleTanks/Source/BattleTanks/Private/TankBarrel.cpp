#include "TankBarrel.h"
#include "CoreMinimal.h"

void UTankBarrel::Elevate(float RelativeSpeed) {

	auto Speed = FMath::Clamp<float>(RelativeSpeed, -4, +4);

	auto ElevationChange = Speed * MaxDegPerSec * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDeg, MaxElevationDeg);

	SetRelativeRotation(FRotator(RawNewElevation, 0, 0));
}