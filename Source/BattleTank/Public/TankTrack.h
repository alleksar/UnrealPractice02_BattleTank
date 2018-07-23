// Done by Aleksa Raicevic

#pragma once

#include "CoreMinimal.h"
#include "../Public/SprungWheel.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);
	//Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxTrackDrivingForce = 40000; //Assume tank has 40tons and 1g acceleration
	
private:
	UTankTrack();
	TArray<class ASprungWheel*> GetWheels() const;
	void DriveTrack(float CurrentThrottle);
	//virtual void BeginPlay() override;
	//void ApplySidewaysForce();
	//UFUNCTION(BlueprintCallable, Category = "Collision")
	//void OnHit(UPrimitiveComponent* HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult &HitResult);
	
	
	
};