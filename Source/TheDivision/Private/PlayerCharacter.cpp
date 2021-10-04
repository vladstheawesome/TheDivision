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

	RifleAttachSocketName = "Rifle_UnequipSocket";
	RifleEquipSocketName = "Rifle_EquipSocket";
	RifleUnEquipSocketName = "Rifle_UnequipSocket";

	PistolAttachSocketName = "Pistol_UnequipSocket";
	PistolEquipSocketName = "Pistol_EquipSocket";
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
		PrimaryWeaponToEquip->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, RifleAttachSocketName);
	}
}

void APlayerCharacter::SpawnSecondaryWeapon(FActorSpawnParameters& SpawnParams)
{
	SecondaryWeaponToEquip = GetWorld()->SpawnActor<APickableItemPistol>(SecondaryWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

	if (SecondaryWeaponToEquip)
	{
		SecondaryWeaponToEquip->SetOwner(this);
		SecondaryWeaponToEquip->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, PistolAttachSocketName);
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

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APlayerCharacter::StopFire);

	PlayerInputComponent->BindAction("Input_EquipPrimaryWeapon", IE_Pressed, this, &APlayerCharacter::TogglePrimaryWeapon);

	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::AddControllerYawInput);
}

void APlayerCharacter::LookUp(float AxisValue)
{

}

void APlayerCharacter::StartFire()
{
	if (EquipedWeapon)
	{
		EquipedWeapon->StartFire();
	}
}

void APlayerCharacter::StopFire()
{
	if (EquipedWeapon)
	{
		EquipedWeapon->StopFire();
	}
}

void APlayerCharacter::TogglePrimaryWeapon()
{
	bPrimaryToEquip = !bPrimaryToEquip;

	if (PrimaryWeaponToEquip)
	{			
		if (auto Anim = Cast<UPlayerAnimations>(GetMesh()->GetAnimInstance()))
		{
			Anim->IsRifleCombatMode = !Anim->IsRifleCombatMode;

			// TODO: Spawn Crosshairs
			// TODO: Refactor if statements -> Create Equip/Unequip methods 
					//(thus can be called by other secondary weapon functions)

			ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

			if (Anim->IsRifleCombatMode == true) // We Equip
			{
				if (MyCharacter)
				{
					GetCharacterMovement()->bOrientRotationToMovement = false;
					bUseControllerRotationYaw = true;
				}

				Anim->AxisTurn_ = InputComponent->GetAxisValue("Turn");;
				EquipedWeapon = PrimaryWeaponToEquip;
				PrimaryWeaponToEquip->SetOwner(this);
				PlayAnimMontage(RifleEquipMontage, 1, NAME_None);
				PrimaryWeaponToEquip->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, RifleEquipSocketName);
			}
			else // We UnEquip
			{
				// Set Equipped Weapon to null?
				GetCharacterMovement()->bOrientRotationToMovement = true;
				bUseControllerRotationYaw = false;

				Anim->AxisTurn_ = 0;
				PrimaryWeaponToEquip->SetOwner(this);
				PlayAnimMontage(RifleUnEquipMontage, 1, NAME_None);
				PrimaryWeaponToEquip->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, RifleUnEquipSocketName);
			}
		}
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

