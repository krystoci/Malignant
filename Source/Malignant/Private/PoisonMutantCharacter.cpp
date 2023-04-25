// Fill out your copyright notice in the Description page of Project Settings.


#include "PoisonMutantCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

APoisonMutantCharacter::APoisonMutantCharacter()
{
}

void APoisonMutantCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APoisonMutantCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APoisonMutantCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APoisonMutantCharacter::Interact()
{
	Super::Interact(); 
}

void APoisonMutantCharacter::MoveForward(float AxisValue)
{
	if (!isWallClimbing)
	{
		Super::MoveForward(AxisValue);
		return;
	}
		
	GetCharacterMovement()->AddInputVector(GetActorUpVector() * AxisValue);

}

void APoisonMutantCharacter::MoveRight(float AxisValue)
{
	if (!isWallClimbing)
	{
		Super::MoveRight(AxisValue);
		return;
	}
		

	Super::MoveRight(AxisValue);

}

void APoisonMutantCharacter::LookUp(float AxisValue)
{
	if (!isWallClimbing)
		Super::LookUp(AxisValue);


}

void APoisonMutantCharacter::LookRight(float AxisValue)
{
	if (!isWallClimbing)
	{
		Super::LookRight(AxisValue);
		return;
	}
		

	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation.Roll += AxisValue;
	SetActorRotation(CurrentRotation);
}

void APoisonMutantCharacter::Jump()
{
	if (!isWallClimbing)
		Super::Jump();
}
