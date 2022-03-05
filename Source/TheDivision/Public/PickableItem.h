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

	virtual void BeginPlay() override;

	void PlayFireEffects(FVector TraceEnd);

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Weapon")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadonly, Category = "Weapon")
	FName MuzzleSocketName;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadonly, Category = "Weapon")
	FName TracerTargetName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* MuzzleEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Weapon")
	UParticleSystem* DefaultImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Weapon")
	UParticleSystem* FleshImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Weapon")
	UParticleSystem* TracerEffect;

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* ItemMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float BaseDamage;

	

	FTimerHandle TimerHandle_TimeBetweenShots;

	float LastFireTime;

	/*RPM - Rounds Per Minute fired*/
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float RateOfFire;

	float TimeBetweenShots;

private:
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;	

	UPROPERTY(VisibleAnywhere)
		USphereComponent* InteractableArea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
		class USoundCue* AssaultRifleFireSound;

public:
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void StartFire();
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void StopFire();

	//UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Fire();

	void Shoot();
};
