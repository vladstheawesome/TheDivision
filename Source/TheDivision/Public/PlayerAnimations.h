// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimations.generated.h"

/**
 * 
 */
UCLASS()
class THEDIVISION_API UPlayerAnimations : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
		bool IsRifleCombatMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
		bool IsPistolCombatMode;
};
