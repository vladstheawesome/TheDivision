// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableItem.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
APickableItem::APickableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	ItemMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(Root);

	InteractableArea = CreateDefaultSubobject<USphereComponent>(TEXT("InteractableArea"));
	InteractableArea->SetupAttachment(ItemMesh);

}

// Called when the game starts or when spawned
void APickableItem::BeginPlay()
{
	Super::BeginPlay();
}

void APickableItem::Fire()
{
	// Trace the world, from pawn eyes to crosshair location (which is the center screen)

	AActor* MyOwner = GetOwner();

	//MyOwner->FindComponentByClass<

	if (MyOwner)
	{
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector TraceEnd = EyeLocation + (EyeRotation.Vector() * 10000);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;

		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility, QueryParams))
		{
			// BLocking hit! Process damage
		}

		DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::White, false, 1.0f, 0, 1.0f);
	}	
}

// Called every frame
void APickableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

