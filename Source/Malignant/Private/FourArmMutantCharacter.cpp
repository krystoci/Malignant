// Fill out your copyright notice in the Description page of Project Settings.


#include "FourArmMutantCharacter.h"

//Set base stats and new components
AFourArmMutantCharacter::AFourArmMutantCharacter()
{
	Label = "FourArmMutant";
	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
}

void AFourArmMutantCharacter::BeginPlay()
{
	Super::BeginPlay();

}

//Called every frame
void AFourArmMutantCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//While holding an object, keep it's location in center camera view
	//THIS WILL NEED TO BE CHANGED
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->GrabbedComponent->SetWorldLocation(LookResult.TraceEnd);
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("%s"), *PhysicsHandle->GrabbedComponent->GetPhysicsLinearVelocity().ToString()));
	}
}

//Expand on action bindings
void AFourArmMutantCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

//Interact with objects
void AFourArmMutantCharacter::Interact()
{
	//If already holding an object, throw it.
	if (PhysicsHandle->GrabbedComponent)
	{
		ThrowObject();
		return;
	}

	//Uses APlayerCharacter::Interact
	Super::Interact();

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("FourArmInteracting")));

	//Attempt to pick up a physics object
	UPrimitiveComponent* HitComponent = LookResult.GetComponent();
	if (HitComponent)
	{
		GrabObject(HitComponent);
	}

}

//Grab physics object
bool AFourArmMutantCharacter::GrabObject(UPrimitiveComponent* HitComponent)
{
	if (HitComponent->IsSimulatingPhysics())
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("ComponentValid")));
		HitComponent->SetSimulatePhysics(false);
		PhysicsHandle->GrabComponentAtLocationWithRotation(HitComponent, NAME_None, HitComponent->GetComponentLocation(), FRotator{ 0.0f, 0.0f, 0.0f });
		return true;
	}
	return false;
}

//Release object and apply impulse in forward facing direction.
void AFourArmMutantCharacter::ThrowObject()
{
	UPrimitiveComponent* ThrowComponent = PhysicsHandle->GrabbedComponent;
	PhysicsHandle->ReleaseComponent();
	ThrowComponent->SetSimulatePhysics(true);
	ThrowComponent->AddImpulse(MainCamera->GetForwardVector() * ThrowStrength, NAME_None, true);
	
	
}

void AFourArmMutantCharacter::LightAttack()
{
}
