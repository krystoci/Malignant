// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "MixingTable.generated.h"

//Forward Declarations
class UUserWidget;
class UBoxComponent;
class APlayerCharacter;
class UCameraComponent;

//To pass values to BottleSelect function
DECLARE_DELEGATE_OneParam(FBottleSelect, const int32)

UCLASS()
class MALIGNANT_API AMixingTable : public AActor, public IInteractable
{
	GENERATED_BODY()



//Methods
public:

	// Sets default values for this actor's properties
	AMixingTable();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Primary function called when this object is interacted with. Overridden from IInteractable
	virtual bool Interact(AActor* CallingActor) override;

	//Blueprint native event to initialize the mixing table widget and begin functionality
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Initialize();

	void Initialize_Implementation();


//Members
public:

	//To set mixing table widget class
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(EditAnywhere)
		UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere)
		UCameraComponent* TableCamera;

//Methods
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


//Members
protected:


	//Values for the interacting player and corresponding controller to recieve input
	UPROPERTY()
		APlayerCharacter* Player;

	UPROPERTY()
		APlayerController* Controller;


//Methods
private:


//Members
private:



	
};
