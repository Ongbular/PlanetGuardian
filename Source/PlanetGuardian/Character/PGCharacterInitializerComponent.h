// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PGCharacterInitializerComponent.generated.h"

class APGCharacter;
class UInputAction;
class UInputMappingContext;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLANETGUARDIAN_API UPGCharacterInitializerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPGCharacterInitializerComponent();

	/** Should be called by the owning pawn when the input component is setup. */
	void InitializePlayerInputComponent(APGCharacter* Owner, UInputComponent* PlayerInputComponent);
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Input | Actions", meta=(AllowPrivateAccess="true"))
	UInputAction* Move;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Input | Actions", meta=(AllowPrivateAccess="true"))
	UInputAction* Look;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Input | Actions", meta=(AllowPrivateAccess="true"))
	UInputAction* Jump;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Input | Actions", meta=(AllowPrivateAccess="true"))
	UInputAction* Crouch;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Input | Mappings", meta=(AllowPrivateAccess="true"))
	UInputMappingContext* BaseLocomotionMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Input | Mappings", meta=(AllowPrivateAccess="true"))
	int32 BaseLocomotionPriority = 0;
};
