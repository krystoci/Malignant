// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "MutagenBase.generated.h"

//Forward Declarations
class UCompoundBase;
class AMutantCharacter;

UCLASS(Blueprintable)
class MALIGNANT_API UMutagenBase : public UItemBase
{
	GENERATED_BODY()
public:

	//Collection of compounds required to successfully brew a potion with this mutagen
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<TSubclassOf<UCompoundBase>> RequiredIngredients;
	
	//Mutant Character that is returned if successfully brewed 
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<AMutantCharacter> MutantClass;
};
