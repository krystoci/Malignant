// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "ProfessorCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MALIGNANT_API AProfessorCharacter : public APlayerCharacter
{
	GENERATED_BODY()

//Methods
public:

	//Attack methods
	virtual void LightAttack() override;
	virtual void HeavyAttack() override;

	//Blueprint native attack events
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void LightAttackEvent();

	void LightAttackEvent_Implementation();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void HeavyAttackEvent();

	void HeavyAttackEvent_Implementation();


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
