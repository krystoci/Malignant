// Fill out your copyright notice in the Description page of Project Settings.


#include "MixingTable.h"
#include "MutantCharacter.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "PlayerCharacter.h"
#include "MalignantGameState.h"
#include "Blueprint/UserWidget.h"


// Sets default values
AMixingTable::AMixingTable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	TableCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TableCamera"));

	RootComponent = BoxCollision;
	BoxCollision->SetBoxExtent({ 64,32,32 });
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Block);

	TableCamera->SetupAttachment(RootComponent);

	TableCamera->SetRelativeRotation({ -15, -90, 0 });
	TableCamera->SetRelativeLocation({ 0, 90, 73 });
}

// Called when the game starts or when spawned
void AMixingTable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMixingTable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AMixingTable::Interact(AActor* CallingActor)
{
	APlayerCharacter* CallingPlayer;
	CallingPlayer = Cast<APlayerCharacter>(CallingActor);
	if(CallingPlayer)
	{
		Player = CallingPlayer;
		Controller = Cast<APlayerController>(Player->GetController());
		Initialize();
		return true;
	}

	return false;
}

void AMixingTable::Initialize_Implementation()
{
}
