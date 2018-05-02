// Done by Aleksa Raicevic

#pragma once



#include "Engine/World.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"


class ATank;
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
	UPROPERTY(EditAnywhere, Category = Setup)
	float AcceptanceRadius = 30.0f; // how close can AI tank get near player
	
	
	
};
