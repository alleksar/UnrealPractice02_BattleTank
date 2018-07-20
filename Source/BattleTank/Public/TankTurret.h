// Done by Aleksa Raicevic

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"


UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	void Rotate(float);
private:
	UPROPERTY(EditAnywhere, Category = "Setup")
	float MaxDegreesPerSeconds = 15.0f;
	
	
};
