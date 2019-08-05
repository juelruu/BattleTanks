#include "AIController.h"
#include "Tank.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	ATank* GetControlledPawn() const;

	ATank* GetPlayerTank() const;

	virtual void BeginPlay() override;

};
