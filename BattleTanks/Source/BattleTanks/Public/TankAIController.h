#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	virtual void BeginPlay() override;
	virtual void SetPawn(APawn* InPawn);
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnPossedTankDeath();

public:
	float AcceptanceRadius = 1000;

};
