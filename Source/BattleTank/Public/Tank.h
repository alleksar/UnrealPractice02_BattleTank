// Done by Aleksa Raicevic

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" //if you put new includes, put them above!!

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()
private:
	ATank();
	virtual void BeginPlay() override;
	int32 StartingHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth = 0;
	UPROPERTY(VisibleAnywhere, Category = "Setup")
	bool bIsPlayerTank;

public:
	/*THIS FUNCTION IS CALLED BY THE ENGINE WHEN DAMAGE IS DEALT*/
	virtual float TakeDamage(float DamageAmount,
							struct FDamageEvent const &DamageEvent,
							class AController * EventInstigator,
							AActor* DamageCauser) override;
	void SetPlayerHealth();
	UFUNCTION(BlueprintCallable, Category = "Check")
	bool PlayerTankAtSight();
	/*THIS FUNCTION RETURNS HP TO BLUEPRINT SO WE CAN UPDATE THE HEALTH BAR*/
	UFUNCTION(BlueprintPure, Category="Health")
	float GetHealthPercentage() const;
	UFUNCTION(BlueprintPure, Category = "Check")
	bool IsPlayerTank() const;
	UPROPERTY(BlueprintAssignable)
	FTankDelegate OnDeath;
	
};
