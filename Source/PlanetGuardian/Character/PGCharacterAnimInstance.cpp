// Fill out your copyright notice in the Description page of Project Settings.


#include "PGCharacterAnimInstance.h"
#include "GameFramework/Character.h"

FPGCharacterAnimInstanceProxy::FPGCharacterAnimInstanceProxy(UAnimInstance* Instance)
	: Super(Instance)
	, Character(nullptr)
	, MovementComponent(nullptr)
	, bIsGameWorld(false)
	, GroundSpeed(0.f)
	, bIsMoving(false)
	, bIsAccelerating(false)
	, bIsInAir(false)
{
}

void FPGCharacterAnimInstanceProxy::InitializeObjects(UAnimInstance* InAnimInstance)
{
	FAnimInstanceProxy::InitializeObjects(InAnimInstance);

	Character = Cast<ACharacter>(InAnimInstance->TryGetPawnOwner());

	if (Character)
	{
		MovementComponent = Character->GetCharacterMovement();
	}
}

void FPGCharacterAnimInstanceProxy::PreUpdate(UAnimInstance* InAnimInstance, float DeltaSeconds)
{
	FAnimInstanceProxy::PreUpdate(InAnimInstance, DeltaSeconds);

	bIsGameWorld = InAnimInstance->GetWorld()->IsGameWorld();
}

void FPGCharacterAnimInstanceProxy::Update(float DeltaSeconds)
{
	FAnimInstanceProxy::Update(DeltaSeconds);

	if (!bIsGameWorld)
	{
		return;
	}
	
	FVector Velocity = Character->GetVelocity();
	Velocity.Z = 0.f;

	GroundSpeed = Velocity.Length();
	bIsMoving = GroundSpeed > MovingTolerance ? true : false;
		
	if (MovementComponent == nullptr)
	{
		return;
	}

	bIsInAir = MovementComponent->IsFalling();
	bIsAccelerating = MovementComponent->GetCurrentAcceleration().IsNearlyZero() ? false : true;	
}

void FPGCharacterAnimInstanceProxy::PostUpdate(UAnimInstance* InAnimInstance) const
{
	FAnimInstanceProxy::PostUpdate(InAnimInstance);

	UPGCharacterAnimInstance* Instance = Cast<UPGCharacterAnimInstance>(InAnimInstance);
	if (Instance)
	{
		Instance->GroundSpeed = GroundSpeed;
		Instance->bIsMoving = bIsMoving;
		Instance->bIsInAir = bIsInAir;
		Instance->bIsAccelerating = bIsAccelerating;
	}
}

FAnimInstanceProxy* UPGCharacterAnimInstance::CreateAnimInstanceProxy()
{
	return new FPGCharacterAnimInstanceProxy(this);
}
