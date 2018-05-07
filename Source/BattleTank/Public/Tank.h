// Done by Aleksa Raicevic

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Tank.generated.h" //if you put new includes, put them above!!



UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()
private:
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth;
public:
	/*THIS FUNCTION IS CALLED BY THE ENGINE WHEN DAMAGE IS DEALT*/
	virtual float TakeDamage(float DamageAmount,
							struct FDamageEvent const &DamageEvent,
							class AController * EventInstigator,
							AActor* DamageCauser) override;
	
};
