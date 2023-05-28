// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StaminaManager.generated.h"

/**
 * 
 */
class ACharacter;


UCLASS()
class MALIGNANT_API UStaminaManager : public UObject
{
	GENERATED_BODY()

public:
	
	UStaminaManager();

	void Initialize(ACharacter* NewOwner, float* StaminaTracker, float BaseStamina);

	UFUNCTION()
	void ClearRefill();

	UFUNCTION()
	void StartRefill();

public:

	//True if stamina is currently being drained
	bool bIsDraining = false;

private:
	UFUNCTION()
	void IncreaseStamina();

private:
	FTimerHandle IncreaseHandle;
	bool bisRefilling = false;

	UPROPERTY()
		ACharacter* OwningPlayer;

	float* StaminaCurrent = nullptr;

	float StaminaBase;

	
};
