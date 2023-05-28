// Fill out your copyright notice in the Description page of Project Settings.


#include "DashComponent.h"
#include "PlayerCharacter.h"
#include "ComboAttackComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values for this component's properties
UDashComponent::UDashComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDashComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UDashComponent::ResetDash(UAnimMontage* PlayedMontage, bool Interrupted)
{
	Player->GetMesh()->GetAnimInstance()->OnMontageEnded.Clear();
	Player->GetMovementComponent()->SetJumpAllowed(true);
	bCanDash = true;
	Player->StaminaStartRefill.ExecuteIfBound();
}

void UDashComponent::ResetAttack(UAnimMontage* PlayedMontage, bool Interrupted)
{
	AttackComponent->bCanAttack = true;
	Player->GetMesh()->GetAnimInstance()->OnMontageBlendingOut.Clear();
}

// Called every frame
void UDashComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDashComponent::Initialize(APlayerCharacter* Owner)
{
	if (Owner)
		Player = Owner;
}

FName UDashComponent::GetDashDirection()
{
	float Forward = (Player->GetCharacterMovement()->Velocity).Dot(Player->GetActorForwardVector());
	float Right = (Player->GetCharacterMovement()->Velocity).Dot(Player->GetActorRightVector());

	if (Forward > 430.0)
		return "FrntDash";
	else if (Forward < -430.0)
		return "BwrdDash";

	if (Right > 400.0)
		return "RightDash";
	else if (Right < -400.0)
		return "LeftDash";

	return "BwrdDash";

}

void UDashComponent::Dash(UComboAttackComponent* AtkComponent)
{
	if ((Player->GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Walking) && bCanDash)
	{
		AttackComponent = AtkComponent;
		if (Player->GetCharacterMovement()->Velocity != FVector{ 0.0, 0.0, 0.0 })
		{
			AttackComponent->bCanAttack = false;
			AttackComponent->bIsAttacking = false;
			Player->GetMovementComponent()->SetJumpAllowed(false);
			bCanDash = false;

			//Play montage and bind delegates 
			Player->PlayAnimMontage(Player->MutantAttackMontage, 1.0f, GetDashDirection());
			Player->GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &UDashComponent::ResetDash);
			Player->GetMesh()->GetAnimInstance()->OnMontageBlendingOut.AddDynamic(this, &UDashComponent::ResetAttack);
			//

			Player->CharacterStats.CurrentStamina -= 20;
			Player->StaminaTaken.ExecuteIfBound();

			FVector Impulse = Player->GetCharacterMovement()->Velocity;
			Impulse.Normalize();
			Player->GetCharacterMovement()->AddImpulse((Impulse * 300.0f) * DashStrength, false);


			/*FTimerDelegate ResetDelegate;
			ResetDelegate.BindUFunction(this, FName("ResetDash"));
			Player->GetWorldTimerManager().SetTimer(DashResetHandle, ResetDelegate, 0.5f, false);*/

		}
	}
		
}

