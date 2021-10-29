// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PickableItem.h"
#include "PlayerAnimations.h"
#include "PlayerCharacter.generated.h" 
class UCameraComponent; class USpringArmComponent;
class APickableItem; class APickableItemPistol; class UPlayerAnimations;
UCLASS()
class THEDIVISION_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnWeapons();
	void SpawnPrimaryWeapon(FActorSpawnParameters& SpawnParams);
	void SpawnSecondaryWeapon(FActorSpawnParameters& SpawnParams);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USpringArmComponent* SpringArmComp;

	APickableItem* EquipedWeapon;
	APickableItem* PrimaryWeaponToEquip;
	APickableItemPistol* SecondaryWeaponToEquip;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TSubclassOf<APickableItem> PrimaryWeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TSubclassOf<APickableItem> SecondaryWeaponClass;

	UPROPERTY(VisibleDefaultsOnly, Category = "Player")
	FName RifleEquipSocketName;

	UPROPERTY(VisibleDefaultsOnly, Category = "Player")
	FName RifleUnEquipSocketName;

	UPROPERTY(VisibleDefaultsOnly, Category = "Player")
	FName PistolEquipSocketName;

	UPROPERTY(VisibleDefaultsOnly, Category = "Player")
	FName PistolUnEquipSocketName;

	void StartFire();

	void StopFire();

	/*void SetCurrentWeapon(class APickableItem* newWeapon, class APickableItem* LastWeapon = nullptr);

	void EquipWeapon(APickableItem* Weapon);*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputCombat")
	bool bPrimaryToEquip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputCombat")
	bool bSecondaryToEquip;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual FVector GetPawnViewLocation() const override;

	void TogglePrimaryWeapon();
	void AttachPrimaryWeaponUnEquip();
	void AttachPrimaryWeaponEquip();

	void ToggleCharacterMovement(bool bWeaponEquiped);

	void ToggleSecondaryWeapon();
	void AttachSecondaryWeaponUnEquip();
	void AttachSecondaryWeaponEquip();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
		UAnimMontage* RifleEquipMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
		UAnimMontage* RifleUnEquipMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
		UAnimMontage* PistolEquipMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
		UAnimMontage* PistolUnEquipMontage;

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> CrossHairRifleClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> CrossHairPistolClass;
};
