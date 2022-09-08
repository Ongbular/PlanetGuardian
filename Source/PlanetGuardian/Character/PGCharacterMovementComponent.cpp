// Fill out your copyright notice in the Description page of Project Settings.


#include "PGCharacterMovementComponent.h"

UPGCharacterMovementComponent::UPGCharacterMovementComponent()
	: Super()
	, CharacterTurnRate(20.f)
{
}

void UPGCharacterMovementComponent::PhysicsRotation(float DeltaTime)
{
	// 부모 클래스인 UCharacterMovementComponent에서는 bOrientRotationToMovement가 켜져 있으면
    // RotationRate를 이용 캐릭터를 회전시킵니다.
    // 이는 RotationRate를 보간할때 일정한 비율(RotationRate)를 이용하기 때문에 회전을 할 때 마다
    // 같은 속도로 캐릭터가 회전하게 됩니다.
    // 아래 코드는 그와는 다르게 보간의 비율을 회전할 때마다 다르게 하여 목표값에 가까울 수록
    // 느리게 회전하여 더욱 부드럽게 회전합니다.
	
    const FRotator CurrentRotation = UpdatedComponent->GetComponentRotation();
    if (Acceleration.Size() > 0.f)
    {
    FRotator TurnTo(FMath::RInterpTo(CurrentRotation, Acceleration.GetSafeNormal().Rotation(), DeltaTime,
    CharacterTurnRate));
    TurnTo.Pitch = 0.f;
    TurnTo.Roll = 0.f;
    TurnTo.Yaw = FRotator::NormalizeAxis(TurnTo.Yaw);
    MoveUpdatedComponent( FVector::ZeroVector, TurnTo, /*bSweep*/ false );
    }

}
