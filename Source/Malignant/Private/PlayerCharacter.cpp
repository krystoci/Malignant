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

//Default Implementation if not overridden in Blueprints
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
	APlayerController* TempCont = Cast<APlayerController>(GetController());
	if (TempCont)
		PController = TempCont;

}

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
	FVector Start = MainCamera->GetComponentLocation();
	FVector End = (MainCamera->GetForwardVector() * LookDistance) + Start;
	GetWorld()->LineTraceSingleByChannel(LookResult, Start, End, ECC_Visibility);
	//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 0.2f, 0, 5.0f);

	//Handle lookat hit result
	HandleTrace();
	
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

//Functions for enabling and disabling player input
void APlayerCharacter::Lock()
{
	if(PController)
		DisableInput(PController);
}

void APlayerCharacter::Release(APlayerController* PCont)
{
	EnableInput(PCont);
}

/*******************************************/


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
		if (DisplayWidget)
			DisplayWidget->RemoveFromViewport();
		IO->Interact(this);
		return;
	}
	return;
}

//If we are looking at an object that is interactable, call HandleDisplay to display the object's widget
void APlayerCharacter::HandleTrace()
{
	IInteractable* IO = Cast<IInteractable>(LookResult.GetActor());
	if (IO && InteractingObject)
		return;

	if ((InteractingObject == nullptr) && IO)
	{
		InteractingObject = IO;
		HandleDisplay(true);
		return;
	
	}
	if (((IO == nullptr) && InteractingObject) || LookResult.bBlockingHit == false)
	{
		HandleDisplay(false);
		InteractingObject = nullptr;
		return;
	}
}

//Display or remove interacting widget from screen
void APlayerCharacter::HandleDisplay(bool Visible)
{
	if (Visible)
	{
		if (TSubclassOf<UUserWidget> Type = InteractingObject->GetWidgetType())
		{
			DisplayWidget = CreateWidget<UUserWidget>(PController, Type);
			DisplayWidget->AddToViewport(0);
		}
		return;
	}
	if(DisplayWidget)
		DisplayWidget->RemoveFromViewport();
}
