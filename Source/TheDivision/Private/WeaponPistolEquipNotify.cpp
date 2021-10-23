// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponPistolEquipNotify.h"
#include "PlayerCharacter.h"
#include "Engine.h"

void UWeaponPistolEquipNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	APlayerCharacter* Owner = Cast<APlayerCharacter>(MeshComp->GetOwner());

	if (Owner)
	{
		Owner->AttachSecondaryWeaponEquip();
	}
}