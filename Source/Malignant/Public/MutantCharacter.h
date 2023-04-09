// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "Containers/EnumAsByte.h"
#include "Chaos/ChaosEngineInterface.h"
#include "MetasoundSource.h"
#include "NiagaraSystem.h"
#include "MutantCharacter.generated.h"

/**
 * 
 */

class UComboAttackComponent;


//This is an abstract class for all mutants to inherit from
UCLASS()
class MALIGNANT_API AMutantCharacter : public APlayerCharacter
{
	GENERATED_BODY()

	/* methods */
public:

	AMutantCharacter();

	//Base methods to be overridden in mutant subclasses
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Interact with objects. Overriden from PlayerCharacter
	virtual void Interact() override;

	//Attack methods
		virtual void LightAttack() override;
		virtual void HeavyAttack() override;


	/* members */
public:

	UPROPERTY(EditAnywhere, Category = Animation)
		UAnimMontage* MutantAttackMontage;

	UPROPERTY(EditAnywhere, Category = Animation)
		TSubclassOf<UComboAttackComponent> AttackComponentClass;

	UPROPERTY(EditAnywhere)
		UComboAttackComponent* AttackComponent;

	/* methods */
protected:



	/* members */
protected:


	/* methods */
private:


	/* members */
private:



	

	
};
