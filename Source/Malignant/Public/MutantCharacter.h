// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "MutantCharacter.generated.h"

//Forward Declarations
class UComboAttackComponent;


//Class defines base functionality shared by all mutants 
UCLASS()
class MALIGNANT_API AMutantCharacter : public APlayerCharacter
{
	GENERATED_BODY()

//Methods
public:

	AMutantCharacter();

	//Base methods to be overridden in mutant subclasses
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Interact with objects. Overriden from PlayerCharacter
	virtual void Interact() override;

	//Attack methods
	virtual void LightAttack() override;
	virtual void HeavyAttack() override;


//Members
public:

	UPROPERTY(EditAnywhere, Category = Animation)
		UAnimMontage* MutantAttackMontage;

	UPROPERTY(EditAnywhere, Category = Animation)
		TSubclassOf<UComboAttackComponent> AttackComponentClass;

	UPROPERTY(EditAnywhere)
		UComboAttackComponent* AttackComponent;

//Methods
protected:

	virtual void BeginPlay() override;

//Members
protected:


//Methods
private:


//Members
private:



	

	
};
