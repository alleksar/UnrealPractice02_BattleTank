// Done by Aleksa Raicevic

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	void AimAt(FVector,float);
	void SetBarrelReference(UTankBarrel *);
	void SetTurretReference(UTankTurret *);


private:
	UTankBarrel *Barrel = nullptr;
	UTankTurret *Turret = nullptr;
	void MoveBarrelTowards(FVector);

		
	
};
