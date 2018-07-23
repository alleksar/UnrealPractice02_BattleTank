// Done by Aleksa Raicevic

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();
	virtual void Tick(float DeltaTime) override;
	void AddDrivingForce(float ForceMagnitude);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//Compontent Section
	void SetupConstraint();
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	void ApplyForce();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* Wheel = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* Axle = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* MassWheelConstraint = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;

	float TotalForceMagnitudeThisFrame = 0;

	

	
	
};
