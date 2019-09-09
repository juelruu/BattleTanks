#include "TankTurret.h"
#include "Tank.h"

void UTankTurret::Rotate(float RelativeSpeed) {

	auto RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);

	auto RotationChange = RelativeSpeed * MaxDegPerSec * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + RotationChange;
	//Rotation = FMath::Clamp<float>(Rotation, -179, +179);

	SetRelativeRotation(FRotator(0, Rotation, 0));
}