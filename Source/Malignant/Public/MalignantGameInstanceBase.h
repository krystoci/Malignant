// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MalignantGameInstanceBase.generated.h"

//Forward Declarations
class UMutagenBase;
class UCompoundBase;
/**
 * 
 */

//Holds a mutagen class and the current amount collected
USTRUCT(BlueprintType, Blueprintable)
struct FMutagens
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UMutagenBase> Mutagen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Amount;
};

//Holds a compound class and the current amount collected
USTRUCT(BlueprintType, Blueprintable)
struct FCompounds
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UCompoundBase> Compound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Amount;
};


UCLASS()
class MALIGNANT_API UMalignantGameInstanceBase : public UGameInstance
{
	GENERATED_BODY()

public:
	//Collection of all available mutagens
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray <FMutagens> AvailableMutagens;

	//Collection of all available compounds
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray <FCompounds> AvailableCompounds;

	UFUNCTION(BlueprintCallable)
		bool DecrementMutagen(TSubclassOf<UMutagenBase> MutagenClass);

	UFUNCTION(BlueprintCallable)
		bool DecrementCompound(TSubclassOf<UCompoundBase> MutagenClass);
	
};
