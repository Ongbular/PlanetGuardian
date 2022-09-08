// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PGCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class PLANETGUARDIAN_API UPGCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UPGCharacterMovementComponent();
	
protected:
	virtual void PhysicsRotation(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float CharacterTurnRate;
};
