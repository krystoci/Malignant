// Fill out your copyright notice in the Description page of Project Settings.


#include "ProfessorCharacter.h"

void AProfessorCharacter::BeginPlay()
{
	Super::BeginPlay();
}

//Theses attack methods are proxies for the Blueprint events
void AProfessorCharacter::LightAttack()
{
	LightAttackEvent();
}

void AProfessorCharacter::HeavyAttack()
{
	HeavyAttackEvent();
}

void AProfessorCharacter::LightAttackEvent_Implementation()
{
}

void AProfessorCharacter::HeavyAttackEvent_Implementation()
{
}
