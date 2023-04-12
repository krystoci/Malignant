// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "ItemPickupBase.generated.h"

//Base class for any item that can be picked up and equipped by the player
UCLASS()
class MALIGNANT_API AItemPickupBase : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemPickupBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual bool Interact(AActor* CallingActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
