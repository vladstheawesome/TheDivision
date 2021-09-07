// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickableItem.h"
#include "PickableItemLauncher.generated.h"

/**
 * 
 */
UCLASS()
class THEDIVISION_API APickableItemLauncher : public APickableItem
{
	GENERATED_BODY()

protected:

	virtual void Fire() override;

	UPROPERTY(EditDefaultsOnly, Category = "ProjectileWeapon")
		TSubclassOf<AActor> ProjectileClass;
	
};
