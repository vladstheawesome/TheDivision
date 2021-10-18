// Fill out your copyright notice in the Description page of Project Settings.

#include "RifleEquipAnimNotify.h"
#include "PlayerCharacter.h"
#include "Engine.h"

void URifleEquipAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	APlayerCharacter* Owner = Cast<APlayerCharacter>(MeshComp->GetOwner());
	Owner->AttachPrimaryWeaponEquip();	
}
