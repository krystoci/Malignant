// Fill out your copyright notice in the Description page of Project Settings.


#include "MutantMapComponent.h"

#include "BoneBladeMutantCharacter.h"
#include "FourArmMutantCharacter.h"
#include "BruteMutantCharacter.h"
#include "FireBreathingMutantCharacter.h"
#include "PoisonMutantCharacter.h"

// Sets default values for this component's properties
UMutantMapComponent::UMutantMapComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bAutoActivate = true;

	//Add class references to the map
	MutantClassMap.Add(EMutantState::EMS_Base, AMutantCharacter::StaticClass());
	MutantClassMap.Add(EMutantState::EMS_Bone, ABoneBladeMutantCharacter::StaticClass());
	MutantClassMap.Add(EMutantState::EMS_FourArm, AFourArmMutantCharacter::StaticClass());
	MutantClassMap.Add(EMutantState::EMS_Brute, ABruteMutantCharacter::StaticClass());
	MutantClassMap.Add(EMutantState::EMS_FireBreathing, AFireBreathingMutantCharacter::StaticClass());
	MutantClassMap.Add(EMutantState::EMS_Poison, APoisonMutantCharacter::StaticClass());

}


// Called when the game starts
void UMutantMapComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMutantMapComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//Accessor for MutantClassMap
TMap<EMutantState, TSubclassOf<AMutantCharacter>> UMutantMapComponent::GetMap()
{
	return MutantClassMap;
}
