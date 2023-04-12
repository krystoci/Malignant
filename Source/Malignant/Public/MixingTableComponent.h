// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MixingTableComponent.generated.h"

//Forwarde Declarations
class UMutagenBase;
class UCompoundBase;
class AMutantCharacter;
struct FMutagens;
struct FCompounds;


UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MALIGNANT_API UMixingTableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UMixingTableComponent();

	//Attempt to return a valid mutant class from ingredients selected 
	UFUNCTION(BlueprintCallable)
		TSubclassOf<AMutantCharacter> Mix(TSubclassOf<UMutagenBase> MutagenClass, TArray<TSubclassOf<UCompoundBase>> Ingredients, bool& isValid);

	//Get all mutagens from GameInstance
	UFUNCTION(BlueprintCallable, BlueprintPure)
		void GetAvailableMutagens(TArray<FMutagens>& AvailableMutagens);

	//Get all compounds from GameInstance
	UFUNCTION(BlueprintCallable, BlueprintPure)
		void GetAvailableCompounds(TArray<FCompounds>& AvailableCompounds);


public:

	//True if a potion has already been created
	UPROPERTY(BlueprintReadWrite)
		bool bPotionIsMade;

	//True if the potion has been made and not drank
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bPotionIsAvailable;
	
	//Mutant class from Mix
	UPROPERTY(BlueprintReadOnly)
		TSubclassOf<AMutantCharacter> MutantClass;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
