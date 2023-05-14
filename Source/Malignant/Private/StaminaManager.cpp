// Fill out your copyright notice in the Description page of Project Settings.


#include "StaminaManager.h"
#include "GameFramework/Character.h"


UStaminaManager::UStaminaManager()
{

}

void UStaminaManager::Initialize(ACharacter* NewOwner, float* StaminaTracker, float BaseStamina)
{
	if (NewOwner)
		OwningPlayer = NewOwner;

	StaminaCurrent = StaminaTracker;
	StaminaBase = BaseStamina;

	
}


void UStaminaManager::ClearRefill()
{
	OwningPlayer->GetWorldTimerManager().ClearTimer(IncreaseHandle);
	
	bisRefilling = false;
}

void UStaminaManager::StartRefill()
{
	if (!bIsDraining)
	{

		FTimerDelegate OnIncreaseDelegate;
		OnIncreaseDelegate.BindUFunction(this, FName("IncreaseStamina"));

		OwningPlayer->GetWorldTimerManager().SetTimer(IncreaseHandle, OnIncreaseDelegate, 0.025, true, 1.0);
	}
}

void UStaminaManager::IncreaseStamina()
{
	*StaminaCurrent += 1;
	if (*StaminaCurrent >= StaminaBase)
	{
		*StaminaCurrent = StaminaBase;
		ClearRefill();
	}
}
