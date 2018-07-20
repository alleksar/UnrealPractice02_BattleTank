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

protected:
	UPROPERTY(EditAnywhere, Category = "Setup") //Consider EditDefaultsOnly..
	float AcceptanceRadius = 3000.0f; // how close can AI tank get near player
private:
	ATankAIController();
	virtual void BeginPlay() override;
	virtual void SetPawn(APawn* InPawn) override;
	virtual void Tick(float) override;
	UFUNCTION(BlueprintCallable, Category = "Check")
	bool PlayerTankAtSight();
	UFUNCTION()
	void OnPossesedTankDeath();
	
	
	
	
};
