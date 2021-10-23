// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableItemPistol.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "TimerManager.h"
#include "TheDivision/TheDivision.h"

//static int32 DebugWeaponDrawing = 0;
//FAutoConsoleVariableRef CVARDebugWeaponDrawing(
//	TEXT("COOP.DebugWeapons"), 
//	DebugWeaponDrawing, 
//	TEXT("Draw Debug Lines for Weapons"), 
//	ECVF_Cheat);

APickableItemPistol::APickableItemPistol()
{
	BaseDamage = 8.0f;

	RateOfFire = 10;
}



