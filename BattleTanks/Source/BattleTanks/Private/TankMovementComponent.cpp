#include "TankMovementComponent.h"
#include "BattleTanks.h"
#include "TankTrack.h"

UTankMovementComponent::UTankMovementComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}


void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}


void UTankMovementComponent::IntentMoveForward(float Throw) {
	if (!ensure(LeftTrack) || !ensure(RightTrack)) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

}

void UTankMovementComponent::IntentRotate(float Throw) {
	if (!ensure(LeftTrack) || !ensure(RightTrack)) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);

	//UE_LOG(LogTemp, Warning, TEXT("Forward Throw: %f"), ForwardThrow);

	auto RotationThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;

	IntentMoveForward(RotationThrow);
	IntentMoveForward(ForwardThrow);
}
