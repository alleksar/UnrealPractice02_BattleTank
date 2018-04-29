// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Tank Player Controller - Begin Play"))

	ATank *Possesed = GetControlledTank();
	if (Possesed == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Player Controller - You are not posessing a tank"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Tank Player Controller - You are posessing a %s"), *(Possesed->GetName()))
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}