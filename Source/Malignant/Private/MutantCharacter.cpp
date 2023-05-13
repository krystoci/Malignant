// Fill out your copyright notice in the Description page of Project Settings.



#include "MutantCharacter.h"
#include "DashComponent.h"
#include "ComboAttackComponent.h"

AMutantCharacter::AMutantCharacter()
{
	//Needs to be disabled due to mixing table functions
	AutoPossessPlayer = EAutoReceiveInput::Disabled;
}

void AMutantCharacter::BeginPlay()
{	
	Super::BeginPlay();

	//Create new attack component
	if (AttackComponentClass)
	{
		AttackComponent = NewObject<UComboAttackComponent>(this, AttackComponentClass, TEXT("AttackComponent"));
	}
	if (AttackComponent)
	{
		AttackComponent->SetSkeletalMeshes(GetMesh(), ThirdPersonBody);
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

void AMutantCharacter::OnDash()
{
	if (DashComponent)
	{
		if (AttackComponent)
		{
			DashComponent->Dash(AttackComponent);
		}
	}
}
