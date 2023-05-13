// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SprintComponent.generated.h"

class APlayerCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MALIGNANT_API USprintComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USprintComponent();

	void Initialize(APlayerCharacter* Owner);

	void Sprint(bool bSprintStarting);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void IncreaseStamina();

	UFUNCTION()
	void DecreaseStamina();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	
	UPROPERTY()
		APlayerCharacter* Player;

	bool bisRefilling = false;
	FTimerHandle DecreaseHandle;
	FTimerHandle IncreaseHandle;

		
};
