#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle) {
	
	FVector ForceApplied = GetForwardVector() * MaxDrivingForce * Throttle;
	FVector ForceLocation = GetComponentLocation();

	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	
	if (TankRoot != nullptr){
		TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

		//UE_LOG(LogTemp, Warning, TEXT("%s force: %s ===> throttle: %f"), TankRoot, *ForceApplied.ToString(), Throttle);
	}
	else{ return; }
	
}

