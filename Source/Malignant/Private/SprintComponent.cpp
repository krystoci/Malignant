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
		Player->StaminaTaken.ExecuteIfBound();
		Player->GetCharacterMovement()->MaxWalkSpeed = Player->CharacterStats.CurrentSprintSpeed;
		Player->GetWorldTimerManager().SetTimer(DecreaseHandle, this, &USprintComponent::DecreaseStamina, 0.05f, true);
	}
	else
	{
		Player->GetWorldTimerManager().ClearTimer(DecreaseHandle);
		Player->GetCharacterMovement()->MaxWalkSpeed = Player->CharacterStats.BaseWalkSpeed;
		Player->StaminaStartRefill.ExecuteIfBound();
	}
}


// Called when the game starts
void USprintComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void USprintComponent::DecreaseStamina()
{
	Player->CharacterStats.CurrentStamina -= 1;
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

