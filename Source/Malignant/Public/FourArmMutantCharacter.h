// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MutantCharacter.h"
#include "FourArmMutantCharacter.generated.h"

//Forward Declarations
class UPhysicsHandleComponent;


UCLASS()
class MALIGNANT_API AFourArmMutantCharacter : public AMutantCharacter
{
	GENERATED_BODY()




	/* methods */
public:

	AFourArmMutantCharacter();

	//Called when actor starts play
	virtual void BeginPlay() override;

	//Called every frame
	virtual void Tick(float DeltaTime) override;

	//Bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Expands functionality for APlayerCharacter::Interact()
	virtual void Interact() override;

	//Attempt to grab a physics object
	bool GrabObject(UPrimitiveComponent* HitComponent);

	//Throw held physics object
	void ThrowObject();

	//Attack method
	virtual void LightAttack() override;


	/* members */
public:


	UPROPERTY(EditAnywhere)
		UPhysicsHandleComponent* PhysicsHandle;

	//How hard to throw objects
	UPROPERTY(EditAnywhere)
		float ThrowStrength = 3000;

	//Trace result when attempting to grab object
	FHitResult GrabHit;



	/* methods */
protected:



	/* members */
protected:



	/* methods */
private:


	/* members */
private:



	
};
