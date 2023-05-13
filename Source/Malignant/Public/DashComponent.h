// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DashComponent.generated.h"

class APlayerCharacter;
class UComboAttackComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MALIGNANT_API UDashComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDashComponent();

//Methods
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void ResetDash(UAnimMontage* PlayedMontage, bool Interrupted);

//Members
protected:

	UPROPERTY()
	APlayerCharacter* Player;

	UPROPERTY(EditAnywhere, Category = Dash)
		float DashStrength = 5000.0;

	UComboAttackComponent* AttackComponent;
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Initialize(APlayerCharacter* Owner);
	FName GetDashDirection();
	void Dash(UComboAttackComponent* AtkComponent);

private:

	FTimerHandle DashResetHandle;
		
};
