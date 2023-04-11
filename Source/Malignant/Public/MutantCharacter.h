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

//MutantCharacter ID for determining in MutantMap
UENUM(BlueprintType)
enum class EMutantState : uint8
{	
	Human = 0, 
	EMS_Base, 
	EMS_Bone, 
	EMS_FourArm, 
	EMS_Brute, 
	EMS_FireBreathing, 
	EMS_Poison 
};


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
	virtual void Interact() override;

	virtual FName GetName();

	//Attack method
	UFUNCTION(BlueprintCallable)
		virtual void LightAttack() override;

	UFUNCTION(BlueprintCallable)
		virtual void HeavyAttack() override;


	/* members */
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AnimationNotify)
		TMap<TEnumAsByte<EPhysicalSurface>, UMetaSoundSource*> MetasoundSolver;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AnimationNotify)
		TMap<TEnumAsByte<EPhysicalSurface>, UNiagaraSystem*> NiagaraSolver;

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

	FName Label = "MutantBase";


	/* methods */
private:


	/* members */
private:



	

	
};
