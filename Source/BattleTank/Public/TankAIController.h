// Done by Aleksa Raicevic

#pragma once

#include "Public/Tank.h"
#include "Engine/World.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
private:
	ATankAIController();
	ATank* GetControlledAITank() const;
	virtual void BeginPlay() override;
	virtual void Tick(float) override;
	ATank* GetPlayerTank() const;
	void AimAtPlayer();
	
	
	
};
