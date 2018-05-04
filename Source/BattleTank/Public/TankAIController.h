// Done by Aleksa Raicevic

#pragma once



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
	virtual void BeginPlay() override;
	virtual void Tick(float) override;
	UPROPERTY(EditAnywhere, Category = "Setup")
	float AcceptanceRadius = 30.0f; // how close can AI tank get near player
	
	
	
};
