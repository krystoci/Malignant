// Fill out your copyright notice in the Description page of Project Settings.


#include "ComboAttackComponent.h"
#include "Animation/AnimMontage.h"

// Sets default values for this component's properties
UComboAttackComponent::UComboAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UComboAttackComponent::LightAttack()
{
	if (!bIsAttacking)
	{
		AttackSection = "LightAttackLeft";
		StartAttack(AttackSection, AttackSpeed);
	}
	if (bComboIsValid())
	{
		switch (GetSectionAsInt(AttackSection))
		{
			case 0:
			{
				AttackSection = "LightAttackRight";
				bPlayNextAttack = true;
				ComboCounter++;
				break;
			}
			case 1:
			{
				AttackSection = "LightAttackLeft";
				bPlayNextAttack = true;
				ComboCounter++;
				break;
			}
			case 3:
			{
				AttackSpeed = 1.0;
				AttackSection = "LightAttackRight";
				bPlayNextAttack = true;
				ComboCounter++;
				break;
			}
		}
	}
}

void UComboAttackComponent::HeavyAttack()
{
	if (!bIsAttacking)
	{
		AttackSection = "HeavyAttack1";
		StartAttack(AttackSection, AttackSpeed);
	}
	if (bComboIsValid())
	{
		switch (GetSectionAsInt(AttackSection))
		{
		case 0:
		{
			AttackSection = "HeavyAttack2";
			bPlayNextAttack = true;
			ComboCounter = 3;
			break;
		}
		case 1:
		{
			AttackSection = "SharpenBladeBoth";
			bPlayNextAttack = true;
			ComboCounter++;
			break;
		}
		case 2:
		{
			AttackSection = "HeavyAttack2";
			AttackSpeed -= 0.25;
			bPlayNextAttack = true;
			ComboCounter++;
			break;
		}
		case 3:
		{
			AttackSection = "HeavyAttack1";
			AttackSpeed -= 0.25;
			bPlayNextAttack = true;
			ComboCounter++;
			break;
		}
		}
	}
}

void UComboAttackComponent::PlayAnimationMontage_Implementation(FName Section, float Speed)
{

}

void UComboAttackComponent::ToggleComboFrame(bool IsWithinComboFrames)
{
	bWithinComboFrames = IsWithinComboFrames;
}

void UComboAttackComponent::FinishAttack()
{
	ToggleComboFrame(false);
	if (bPlayNextAttack)
	{
		StartAttack(AttackSection, AttackSpeed);
		return;
	}
	if (ComboCounter > 2)
	{
		FTimerHandle ComboDelay;
		GetOwner()->GetWorldTimerManager().SetTimer(ComboDelay, this, &UComboAttackComponent::Reset, 0.6, false);
		return;
	}
	Reset();
}

void UComboAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UComboAttackComponent::StartAttack(FName Section, float Speed)
{

	bIsAttacking = true;
	bPlayNextAttack = false;
	PlayAnimationMontage(Section, Speed);
}

void UComboAttackComponent::SetSkeletalMeshes(USkeletalMeshComponent* FPSkeleton, USkeletalMeshComponent* TPSkeleton)
{
	FirstPersonSkeleton = FPSkeleton;
	ThirdPersonSkeleton = TPSkeleton;
}

void UComboAttackComponent::SetAttackMontage(UAnimMontage* Montage)
{
	AttackMontage = Montage;
}

// Called when the game starts
void UComboAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	AttackSpeed = StartingAttackSpeed;
	// ...
	
}

bool UComboAttackComponent::bComboIsValid()
{
	if (bWithinComboFrames && (ComboCounter < 3) && !bPlayNextAttack)
	{
		return true;
	}
	return false;
}

uint32 UComboAttackComponent::GetSectionAsInt(FName Section)
{
	uint32 SectionNumber = 0;

	if (Section == "LightAttackLeft")
		SectionNumber = 0;
	if (Section == "LightAttackRight")
		SectionNumber = 1;
	if (Section == "HeavyAttack1")
		SectionNumber = 2;
	if (Section == "HeavyAttack2")
		SectionNumber = 3;
	if (Section == "SharpenBladeBoth")
		SectionNumber = 4;

	//Add more as needed

	return SectionNumber;
}

void UComboAttackComponent::Reset()
{
	bIsAttacking = false;
	bPlayNextAttack = false;
	ComboCounter = 1;
	AttackSpeed = StartingAttackSpeed;
}


