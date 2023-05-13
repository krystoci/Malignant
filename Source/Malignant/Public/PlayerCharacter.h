// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Delegates/Delegate.h"
#include "PlayerCharacter.generated.h"

//Forward Declarations
class UStaticMeshComponent;
class UCameraComponent;
class IInteractable;
class AItemPickupBase;
class UDashComponent;
class USprintComponent;

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCameraLookUp, float, AxisValue);

DECLARE_DELEGATE_OneParam(FOnSprintPressed, bool);

USTRUCT(BlueprintType, Blueprintable)
struct FCharacterStats
{
	GENERATED_BODY()

	FCharacterStats()
	{
		CurrentHealth = BaseHealth;
		CurrentDefense = BaseDefense;
		CurrentAttack = BaseAttack;
		CurrentStamina = BaseStamina;
		CurrentSprintSpeed = BaseSprintSpeed;
	}

	//Default Stat Values
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BaseHealth = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BaseDefense = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BaseAttack = 20.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BaseWalkSpeed = 600.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BaseStamina = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BaseSprintSpeed = 100.0f;
	
	//Stat values at any given time to be used at runtime
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CurrentDefense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CurrentAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CurrentStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CurrentSprintSpeed;

};


UCLASS()
class MALIGNANT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()


	/* methods */
public:

	UPROPERTY(BlueprintAssignable)
	FOnCameraLookUp OnCameraLookUp;


	// Sets default values for this pawn's properties
	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Movement Functions
	virtual void MoveForward(float AxisValue);
	virtual void MoveRight(float AxisValue);
	virtual void LookUp(float AxisValue);
	virtual void LookRight(float AxisValue);
	virtual void Jump();
	virtual void OnDash();
	
	UFUNCTION()
	virtual void OnSprint(bool bisStarting);
	

	//Used to interact with IInteractables 
	virtual void Interact();

	//Attack methods
	UFUNCTION(BlueprintCallable)
	virtual void LightAttack();

	UFUNCTION(BlueprintCallable)
	virtual void HeavyAttack();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void EquipItem(AItemPickupBase* NewItem);

	void EquipItem_Implementation(AItemPickupBase* NewItem);


	/* members */
public:

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* FirstPersonBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* ThirdPersonBody;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		UCameraComponent* MainCamera;

	UPROPERTY(EditAnywhere, Category = Dash)
		UDashComponent* DashComponent;

	UPROPERTY(EditAnywhere, Category = SprintDash)
		USprintComponent* SprintComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FCharacterStats CharacterStats;

	//May change the name of this later cause I had to move it to PlayerCharacter
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
		UAnimMontage* MutantAttackMontage;

	//Object currently being interacted with or viewed and interactable
	IInteractable* InteractingObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AItemPickupBase* EquippedItem;

	//Default distance for line trace
	UPROPERTY(EditAnywhere, Category = Traces)
		float LookDistance = 200;


	/* methods */
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* members */
protected:
	

	//Pointer to PlayerController to avoid casting
	UPROPERTY()
		APlayerController* PController;

	//Result from line trace
	FHitResult LookResult;


	/* methods */
private:

	void SetCharacterVisiblity();
	/* members */
private:




};
