// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Blueprint/UserWidget.h"
#include "ItemPickupBase.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//Create and setup default components
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	StaticMesh->SetupAttachment(RootComponent);
	MainCamera->SetupAttachment(RootComponent);
	MainCamera->SetRelativeLocation({ 0.0f, 0.0f, 60.0f });

	GetCharacterMovement()->SetUpdatedComponent(RootComponent);
	bUseControllerRotationYaw = true;

}

//Default Equip Implementation if not overridden in Blueprints
void APlayerCharacter::EquipItem_Implementation(AItemPickupBase* NewItem)
{
	EquippedItem = NewItem;
	FAttachmentTransformRules AttachRules{ EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false };
	NewItem->AttachToComponent(MainCamera, AttachRules);

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Store player controller
	PController = Cast<APlayerController>(GetController());

}

//Attack Methods
void APlayerCharacter::LightAttack()
{
}

void APlayerCharacter::HeavyAttack()
{
}


// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Look trace
	//THIS NEEDS TO BE MOVED TO THE CONTROLLER IN A TIMER FUNCTION
	FVector Start = MainCamera->GetComponentLocation();
	FVector End = (MainCamera->GetForwardVector() * LookDistance) + Start;
	GetWorld()->LineTraceSingleByChannel(LookResult, Start, End, ECC_Visibility);
	//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 0.2f, 0, 5.0f);
	
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	InputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);
	InputComponent->BindAxis("LookRight", this, &APlayerCharacter::LookRight);
	InputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);
	InputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact);
	InputComponent->BindAction("LightAttack", IE_Pressed, this, &APlayerCharacter::LightAttack);
	InputComponent->BindAction("HeavyAttack", IE_Pressed, this, &APlayerCharacter::HeavyAttack);

}


//Movement Functions
void APlayerCharacter::MoveForward(float AxisValue)
{
	if (GetCharacterMovement())
		GetCharacterMovement()->AddInputVector(GetActorForwardVector() * AxisValue);

}

void APlayerCharacter::MoveRight(float AxisValue)
{
	if (GetCharacterMovement())
		GetCharacterMovement()->AddInputVector(GetActorRightVector() * AxisValue);
}

void APlayerCharacter::LookUp(float AxisValue)
{

	FRotator CurrentRotation = MainCamera->GetRelativeRotation();
	FRotator NewRotation = CurrentRotation;
	NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + AxisValue, -89.0, 89.0);
	MainCamera->SetRelativeRotation(NewRotation);

	OnCameraLookUp.Broadcast(AxisValue);
}

void APlayerCharacter::LookRight(float AxisValue)
{

	FRotator CurrentRotation = GetControlRotation();
	CurrentRotation.Yaw += AxisValue;
	GetController()->SetControlRotation(CurrentRotation);
}

void APlayerCharacter::Jump()
{
	if (GetCharacterMovement())
	{
		ACharacter::Jump();
	}
}

//Handle Interaction with objects 
void APlayerCharacter::Interact()
{

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Interacting!")));

	//If nothing is within LookDistance then return.
	if (!LookResult.GetActor())
		return;

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Actor Valid")));
	
	//Check to see if we can interact with an object, and if so, interact with it
	IInteractable* IO = Cast<IInteractable>(LookResult.GetActor());
	if (IO)
	{
		IO->Interact(this);
		return;
	}
	return;
}

