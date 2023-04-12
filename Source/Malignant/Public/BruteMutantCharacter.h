// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MutantCharacter.h"
#include "BruteMutantCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MALIGNANT_API ABruteMutantCharacter : public AMutantCharacter
{
	GENERATED_BODY()


//Methods
public:

	ABruteMutantCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Interact() override;

//Members
public:


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
