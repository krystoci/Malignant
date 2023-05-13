// Fill out your copyright notice in the Description page of Project Settings.


#include "SprintComponent.h"
#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
USprintComponent::USprintComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void USprintComponent::Initialize(APlayerCharacter* Owner)
{
	if (Owner)
		Player = Owner;
}

void USprintComponent::Sprint(bool bSprintStarting)
{
	if (bSprintStarting)
	{
		bisRefilling = false;
		Player->GetWorldTimerManager().ClearTimer(IncreaseHandle);
		Player->GetCharacterMovement()->MaxWalkSpeed = Player->CharacterStats.CurrentSprintSpeed;
		Player->GetWorldTimerManager().SetTimer(DecreaseHandle, this, &USprintComponent::DecreaseStamina, 0.1f, true);
	}
	else
	{
		Player->GetWorldTimerManager().ClearTimer(DecreaseHandle);
		if (!bisRefilling)
		{
			Player->GetCharacterMovement()->MaxWalkSpeed = Player->CharacterStats.BaseWalkSpeed;
			Player->GetWorldTimerManager().SetTimer(IncreaseHandle, this, &USprintComponent::IncreaseStamina, 0.05f, true, 2.0);
			bisRefilling = true;
		}
	}
}


// Called when the game starts
void USprintComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void USprintComponent::IncreaseStamina()
{
	Player->CharacterStats.CurrentStamina += 2;
	if (Player->CharacterStats.CurrentStamina >= Player->CharacterStats.BaseStamina)
	{
		Player->CharacterStats.CurrentStamina = Player->CharacterStats.BaseStamina;
		Player->GetWorldTimerManager().ClearTimer(IncreaseHandle);
		bisRefilling = false;
	}
}

void USprintComponent::DecreaseStamina()
{
	Player->CharacterStats.CurrentStamina -= 2;
	if (Player->CharacterStats.CurrentStamina <= 0.0f)
	{
		Sprint(false);
	}
}


// Called every frame
void USprintComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

