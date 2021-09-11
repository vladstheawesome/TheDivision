// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableItemLauncher.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

//void APickableItemLauncher::Fire()
//{
//	AActor* MyOwner = GetOwner();
//
//	if (MyOwner && ProjectileClass)
//	{
//		FVector EyeLocation;
//		FRotator EyeRotation;
//		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
//
//		FVector MuzzleLocation = ItemMesh->GetSocketLocation(MuzzleSocketName);
//		//FRotator MuzzleRotation = ItemMesh->GetSocketRotation(MuzzleSocketName);
//
//		FActorSpawnParameters SpawnParams;
//		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
//
//		GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, EyeRotation, SpawnParams);
//	}
//}