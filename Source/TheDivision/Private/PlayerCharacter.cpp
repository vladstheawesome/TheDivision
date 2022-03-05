// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PickableItem.h"
#include "PickableItemPistol.h"
#include "PlayerAnimations.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Sound/SoundCue.h"

class UPawnMovementComponent;
// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	RifleEquipSocketName = "Rifle_EquipSocket";
	RifleUnEquipSocketName = "Rifle_UnequipSocket";

	PistolEquipSocketName = "Pistol_EquipSocket";
	PistolUnEquipSocketName = "Pistol_UnequipSocket";
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapons();	
}

void APlayerCharacter::SpawnWeapons()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	SpawnPrimaryWeapon(SpawnParams);
	SpawnSecondaryWeapon(SpawnParams);
}

void APlayerCharacter::SpawnPrimaryWeapon(FActorSpawnParameters& SpawnParams)
{
	PrimaryWeaponToEquip = GetWorld()->SpawnActor<APickableItem>(PrimaryWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

	if (PrimaryWeaponToEquip)
	{
		PrimaryWeaponToEquip->SetOwner(this);
		PrimaryWeaponToEquip->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, RifleUnEquipSocketName);
	}
}

void APlayerCharacter::SpawnSecondaryWeapon(FActorSpawnParameters& SpawnParams)
{
	SecondaryWeaponToEquip = GetWorld()->SpawnActor<APickableItemPistol>(SecondaryWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

	if (SecondaryWeaponToEquip)
	{
		SecondaryWeaponToEquip->SetOwner(this);
		SecondaryWeaponToEquip->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, PistolUnEquipSocketName);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("FireButton", IE_Pressed, this, &APlayerCharacter::StartFire);
	PlayerInputComponent->BindAction("FireButton", IE_Released, this, &APlayerCharacter::StopFire);

	PlayerInputComponent->BindAction("Input_EquipPrimaryWeapon", IE_Pressed, this, &APlayerCharacter::TogglePrimaryWeapon);
	PlayerInputComponent->BindAction("Input_EquipSecondaryWeapon", IE_Pressed, this, &APlayerCharacter::ToggleSecondaryWeapon);
}

void APlayerCharacter::StartFire()
{
	if (EquipedWeapon)
	{
		//EquipedWeapon->StartFire();
		UE_LOG(LogTemp, Warning, TEXT("Fire Weapon!"));

		EquipedWeapon->Shoot();		
	}
}

void APlayerCharacter::StopFire()
{
	if (EquipedWeapon)
	{
		//EquipedWeapon->StopFire();
	}
}

/*Primary Weapon Functions*/
void APlayerCharacter::TogglePrimaryWeapon()
{
	bPrimaryToEquip = !bPrimaryToEquip;
	UUserWidget* CrossHairRifle = CreateWidget(GetWorld(), CrossHairRifleClass);

	// Disable/Remove any Secondary Weapon Items, if previously equipped
	if (bSecondaryToEquip) 
	{
		bSecondaryToEquip = !bSecondaryToEquip;
		AttachSecondaryWeaponUnEquip();
		UWidgetLayoutLibrary::RemoveAllWidgets(this);
	}

	if (PrimaryWeaponToEquip)
	{			
		if (auto Anim = Cast<UPlayerAnimations>(GetMesh()->GetAnimInstance()))
		{
			Anim->IsRifleCombatMode = !Anim->IsRifleCombatMode;

			if (Anim->IsRifleCombatMode == true) // We Equip Rifle
			{				
				ToggleCharacterMovement(bPrimaryToEquip);
				EquipedWeapon = PrimaryWeaponToEquip;
				PlayAnimMontage(RifleEquipMontage, 1, NAME_None);

				if (CrossHairRifle != nullptr)
				{
					CrossHairRifle->AddToViewport();
				}
			}
			else // We UnEquip Rifle
			{				
				ToggleCharacterMovement(bPrimaryToEquip);
				EquipedWeapon = nullptr;
				PlayAnimMontage(RifleUnEquipMontage, 1, NAME_None);
				UWidgetLayoutLibrary::RemoveAllWidgets(this);
			}
		}
	}	
}

void APlayerCharacter::AttachPrimaryWeaponUnEquip()
{
	PrimaryWeaponToEquip->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, RifleUnEquipSocketName);
}

void APlayerCharacter::AttachPrimaryWeaponEquip()
{
	PrimaryWeaponToEquip->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, RifleEquipSocketName);
}

/*Secondary Weapon Functions*/
void APlayerCharacter::ToggleSecondaryWeapon()
{
	bSecondaryToEquip = !bSecondaryToEquip;
	UUserWidget* CrossHairPistol = CreateWidget(GetWorld(), CrossHairPistolClass);

	if (bPrimaryToEquip)
	{
		bPrimaryToEquip = !bPrimaryToEquip;
		AttachPrimaryWeaponUnEquip();
		UWidgetLayoutLibrary::RemoveAllWidgets(this);
	}

	if (SecondaryWeaponToEquip)
	{
		if (auto Anim = Cast<UPlayerAnimations>(GetMesh()->GetAnimInstance()))
		{
			Anim->IsPistolCombatMode = !Anim->IsPistolCombatMode;

			if (Anim->IsPistolCombatMode) // We  Equip Pistol
			{
				ToggleCharacterMovement(bSecondaryToEquip);
				EquipedWeapon = SecondaryWeaponToEquip;
				PlayAnimMontage(PistolEquipMontage, 1, NAME_None);

				if (CrossHairPistol != nullptr)
				{
					CrossHairPistol->AddToViewport();
				}
			}
			else
			{
				ToggleCharacterMovement(bSecondaryToEquip);
				EquipedWeapon = nullptr;
				PlayAnimMontage(PistolUnEquipMontage, 1, NAME_None);
				UWidgetLayoutLibrary::RemoveAllWidgets(this);
			}
		}
	}
}

void APlayerCharacter::AttachSecondaryWeaponUnEquip()
{
	SecondaryWeaponToEquip->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, PistolUnEquipSocketName);
}

void APlayerCharacter::AttachSecondaryWeaponEquip()
{
	SecondaryWeaponToEquip->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, PistolEquipSocketName);
}

/*Switch/Toggle Movement Mode*/
void APlayerCharacter::ToggleCharacterMovement(bool bWeaponEquiped)
{
	if (bWeaponEquiped)
	{
		GetCharacterMovement()->bOrientRotationToMovement = false;
		bUseControllerRotationYaw = true;
	}
	else
	{
		GetCharacterMovement()->bOrientRotationToMovement = true;
		bUseControllerRotationYaw = false;
	}
}

FVector APlayerCharacter::GetPawnViewLocation() const
{
	if (CameraComp)
	{
		return CameraComp->GetComponentLocation();
	}

	return Super::GetPawnViewLocation();
}

