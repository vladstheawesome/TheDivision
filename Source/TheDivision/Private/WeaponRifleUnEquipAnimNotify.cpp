// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponRifleUnEquipAnimNotify.h"
#include "PlayerCharacter.h"
#include "Engine.h"

void UWeaponRifleUnEquipAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	APlayerCharacter* Owner = Cast<APlayerCharacter>(MeshComp->GetOwner());

	if (Owner)
	{		
		Owner->AttachPrimaryWeaponUnEquip();
	}
}
