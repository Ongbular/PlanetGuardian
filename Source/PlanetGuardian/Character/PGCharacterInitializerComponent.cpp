// Fill out your copyright notice in the Description page of Project Settings.


#include "PGCharacterInitializerComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PGCharacter.h"

UPGCharacterInitializerComponent::UPGCharacterInitializerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPGCharacterInitializerComponent::InitializePlayerInputComponent(APGCharacter* Owner, UInputComponent* PlayerInputComponent)
{
	const APlayerController* PC = Owner->GetController<APlayerController>();
	check(PC);

	const ULocalPlayer* LP = PC->GetLocalPlayer();
	check(LP);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(BaseLocomotionMappingContext, BaseLocomotionPriority);
	
	if (UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (Jump)
		{
			PlayerEnhancedInputComponent->BindAction(Jump, ETriggerEvent::Triggered, Owner, &ACharacter::Jump);
		}

		if (Move)
		{
			PlayerEnhancedInputComponent->BindAction(Move, ETriggerEvent::Triggered, Owner, &APGCharacter::Input_Move);
		}

		if (Look)
		{
			PlayerEnhancedInputComponent->BindAction(Look, ETriggerEvent::Triggered, Owner, &APGCharacter::Input_Look);
		}
	}
}


void UPGCharacterInitializerComponent::BeginPlay()
{
	Super::BeginPlay();
	
}
