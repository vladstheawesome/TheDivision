// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickableItem.h"
#include "PickableItemPistol.generated.h"

/**
 * 
 */
UCLASS()
class THEDIVISION_API APickableItemPistol : public APickableItem
{
	GENERATED_BODY()
	
protected:

	virtual void Fire() override;
};
