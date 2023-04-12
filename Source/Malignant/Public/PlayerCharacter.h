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

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCameraLookUp, float, AxisValue);

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
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		UCameraComponent* MainCamera;

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


	/* members */
private:




};
