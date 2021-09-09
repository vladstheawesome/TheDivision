// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "PickableItem.generated.h"
class UDamageType;
class UParticleSystem;
UCLASS()
class THEDIVISION_API APickableItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickableItem();

protected:

	void PlayFireEffects(FVector TraceEnd);

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Weapon")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadonly, Category = "Weapon")
	FName MuzzleSocketName;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadonly, Category = "Weapon")
	FName TracerTargetName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Weapon")
	UParticleSystem* MuzzleEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Weapon")
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Weapon")
	UParticleSystem* TracerEffect;

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* ItemMesh;
private:
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;
	

	UPROPERTY(VisibleAnywhere)
		USphereComponent* InteractableArea;

public:

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		virtual void Fire();


};
