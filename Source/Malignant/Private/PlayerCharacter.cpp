// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Blueprint/UserWidget.h"
#include "ItemPickupBase.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Interactable.h"
#include "DashComponent.h"
#include "SprintComponent.h"
#include "StaminaManager.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//Create and setup default components
	//StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	FirstPersonBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonSkeleton"));
	ThirdPersonBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ThirdPersonSkeleton"));
	DashComponent = CreateDefaultSubobject<UDashComponent>(TEXT("DashComponent"));
	SprintComponent = CreateDefaultSubobject<USprintComponent>(TEXT("SprintComponent"));

	FirstPersonBody->SetupAttachment(RootComponent);
	ThirdPersonBody->SetupAttachment(RootComponent);
	//StaticMesh->SetupAttachment(RootComponent);
	
	GetCharacterMovement()->SetUpdatedComponent(RootComponent);
	bUseControllerRotationYaw = true;

	CharacterStats.BaseWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	

	
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
	SetCharacterVisiblity();

	const USkeletalMeshSocket* CameraSocket = FirstPersonBody->GetSocketByName("cameraSocket");
	if (CameraSocket)
	{
		MainCamera->SetupAttachment(FirstPersonBody, FName("cameraSocket"));
	}
	/*else
	{
		MainCamera->SetupAttachment(RootComponent);
		MainCamera->SetRelativeLocation({ 0.0f, 0.0f, 60.0f });
	}*/

	DashComponent->Initialize(this);
	SprintComponent->Initialize(this);

	PlayerStaminaManager = NewObject<UStaminaManager>(UStaminaManager::StaticClass());
	PlayerStaminaManager->Initialize(this, &CharacterStats.CurrentStamina, CharacterStats.BaseStamina);
	StaminaTaken.BindUFunction(PlayerStaminaManager, FName("ClearRefill"));
	StaminaStartRefill.BindUFunction(PlayerStaminaManager, FName("StartRefill"));

}

void APlayerCharacter::SetCharacterVisiblity()
{
	GetMesh()->SetOnlyOwnerSee(true);
	ThirdPersonBody->SetOwnerNoSee(true);
	FirstPersonBody->SetOnlyOwnerSee(true);
	FirstPersonBody->HideBoneByName("l_bicep", EPhysBodyOp::PBO_None);
	FirstPersonBody->HideBoneByName("r_bicep", EPhysBodyOp::PBO_None);
	FirstPersonBody->HideBoneByName("neck", EPhysBodyOp::PBO_None);
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
	InputComponent->BindAction("Dash", IE_Pressed, this, &APlayerCharacter::OnDash);
	InputComponent->BindAction<FOnSprintPressed>("Sprint", IE_Pressed, this, &APlayerCharacter::OnSprint, true);
	InputComponent->BindAction<FOnSprintPressed>("Sprint", IE_Released, this, &APlayerCharacter::OnSprint, false);


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

	//FRotator CurrentRotation = MainCamera->GetRelativeRotation();
	//FRotator CurrentRotation = GetMesh()->GetSocketRotation("spine3");
	//FRotator NewRotation = CurrentRotation;
	//NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + AxisValue, -89.0, 89.0);
	//MainCamera->SetRelativeRotation(NewRotation);
	//GetMesh()->GetAnimationBl

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

void APlayerCharacter::OnDash()
{
	//Overridden in MutantCharacter to pass the Attack Component
}

void APlayerCharacter::OnSprint(bool bisStarting)
{
	PlayerStaminaManager->bIsDraining = bisStarting;
	SprintComponent->Sprint(bisStarting);
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

