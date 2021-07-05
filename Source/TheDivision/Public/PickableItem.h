// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "PickableItem.generated.h"

class UDamageType;
UCLASS()
class THEDIVISION_API APickableItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickableItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Fire();

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Weapon")
	TSubclassOf<UDamageType> DamageType;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* ItemMesh;

	UPROPERTY(VisibleAnywhere)
		USphereComponent* InteractableArea;

};
