// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MalignantGameState.generated.h"

/**
 * 
 */
UCLASS()
class MALIGNANT_API AMalignantGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
		UFUNCTION(BlueprintNativeEvent)
			void SpawnPlayer(EMutantState CharacterClass);

		void SpawnPlayer_Implementation(EMutantState CharacterClass);
	
};
