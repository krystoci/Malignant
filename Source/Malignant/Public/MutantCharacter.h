// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "MutantCharacter.generated.h"

//Forward Declarations
class UComboAttackComponent;


<<<<<<< HEAD
//Class defines base functionality shared by all mutants 
=======
//This is an abstract class for all mutants to inherit from
>>>>>>> parent of bcc2c88 (Added security room assets including grey locker, mug, chair, milk crates, and all the basecolor, metallic, normal and roughness maps)
UCLASS()
class MALIGNANT_API AMutantCharacter : public APlayerCharacter
{
	GENERATED_BODY()

<<<<<<< HEAD
//Methods
=======
	/* methods */
>>>>>>> parent of bcc2c88 (Added security room assets including grey locker, mug, chair, milk crates, and all the basecolor, metallic, normal and roughness maps)
public:

	AMutantCharacter();

	//Base methods to be overridden in mutant subclasses
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Interact with objects. Overriden from PlayerCharacter
	virtual void Interact() override;

	//Attack methods
<<<<<<< HEAD
	virtual void LightAttack() override;
	virtual void HeavyAttack() override;
=======
		virtual void LightAttack() override;
		virtual void HeavyAttack() override;
>>>>>>> parent of bcc2c88 (Added security room assets including grey locker, mug, chair, milk crates, and all the basecolor, metallic, normal and roughness maps)


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


<<<<<<< HEAD
//Methods
=======

	/* members */
protected:


	/* methods */
>>>>>>> parent of bcc2c88 (Added security room assets including grey locker, mug, chair, milk crates, and all the basecolor, metallic, normal and roughness maps)
private:


//Members
private:



	

	
};
