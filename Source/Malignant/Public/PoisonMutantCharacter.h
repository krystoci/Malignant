// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MutantCharacter.h"
#include "PoisonMutantCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MALIGNANT_API APoisonMutantCharacter : public AMutantCharacter
{
	GENERATED_BODY()

public:
	APoisonMutantCharacter();

	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Interact() override;

	//Movement functions overridden due to wall climbing capabilities 
	void MoveForward(float AxisValue) override;
	void MoveRight(float AxisValue) override;
	void LookUp(float AxisValue) override;
	void LookRight(float AxisValue) override;
	void Jump() override;

public:

	UPROPERTY(BlueprintReadWrite)
		bool isWallClimbing;

protected:

	virtual void BeginPlay() override;

protected:


private:



private:
	
};
