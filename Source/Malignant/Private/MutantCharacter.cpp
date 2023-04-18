// Fill out your copyright notice in the Description page of Project Settings.



#include "MutantCharacter.h"

#include "ComboAttackComponent.h"

AMutantCharacter::AMutantCharacter()
{
	AutoPossessPlayer = EAutoReceiveInput::Disabled;
}

void AMutantCharacter::BeginPlay()
{

	
	Super::BeginPlay();

	if (AttackComponentClass)
	{
		AttackComponent = NewObject<UComboAttackComponent>(this, AttackComponentClass, TEXT("AttackComponent"));
	}
	if (AttackComponent)
	{
		AttackComponent->SetSkeletalMesh(GetMesh());
		AttackComponent->SetAttackMontage(MutantAttackMontage);
	}
}

void AMutantCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMutantCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMutantCharacter::Interact()
{
	//Uses APlayerCharacter::Interact
	Super::Interact();

}

FName AMutantCharacter::GetName()
{
	return Label;
}

void AMutantCharacter::LightAttack()
{
	if(AttackComponent)
		AttackComponent->LightAttack();
}

void AMutantCharacter::HeavyAttack()
{
	if(AttackComponent)
		AttackComponent->HeavyAttack();
}
