// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimInstanceProxy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PGCharacterAnimInstance.generated.h"

USTRUCT()
struct FPGCharacterAnimInstanceProxy : public FAnimInstanceProxy
{
	GENERATED_BODY()
	
public:
	FPGCharacterAnimInstanceProxy() = default;
	FPGCharacterAnimInstanceProxy(UAnimInstance* Instance);
	
protected:
	virtual void InitializeObjects(UAnimInstance* InAnimInstance) override;

	virtual void PreUpdate(UAnimInstance* InAnimInstance, float DeltaSeconds) override;
	virtual void Update(float DeltaSeconds) override;
	virtual void PostUpdate(UAnimInstance* InAnimInstance) const override;

private:
	constexpr static float MovingTolerance = 5.f;
	
	UPROPERTY()
	ACharacter* Character;

	UPROPERTY()
	UCharacterMovementComponent* MovementComponent;

	bool bIsGameWorld;
	float GroundSpeed;
	bool bIsMoving;
	bool bIsAccelerating;
	bool bIsInAir;
};

/**
 * 
 */
UCLASS()
class PLANETGUARDIAN_API UPGCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	friend struct FPGCharacterAnimInstanceProxy;
	
protected:
	virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float GroundSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	bool bIsMoving;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	bool bIsAccelerating;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	bool bIsInAir;
};
