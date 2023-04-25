// Fill out your copyright notice in the Description page of Project Settings.


#include "BoneBladeMutantCharacter.h"

ABoneBladeMutantCharacter::ABoneBladeMutantCharacter()
{
}

void ABoneBladeMutantCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABoneBladeMutantCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoneBladeMutantCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABoneBladeMutantCharacter::Interact()
{
	//Uses APlayerCharacter::Interact
	Super::Interact();
}

