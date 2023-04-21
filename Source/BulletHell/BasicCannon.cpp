// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicCannon.h"
#include "BasicProjectile.h"
#include "Engine.h"

ABasicCannon::ABasicCannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(
		TEXT("AudioComp")
		);
}

// Called when the game starts or when spawned
void ABasicCannon::BeginPlay()
{
	Super::BeginPlay();
	_Timer = 1 / _FireRate;

	AudioComponent->bAutoActivate = false;

	if (ShotSound->IsValidLowLevelFast()) {
		AudioComponent->SetSound(ShotSound);
	}
}

// Called every frame
void ABasicCannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	_Timer -= DeltaTime;
	if (_Timer <= 0)
	{
		_Timer = 1 / _FireRate;
		Fire();
	}
}

void ABasicCannon::Fire()
{
	ABasicProjectile* tmp = GetWorld()->SpawnActor<ABasicProjectile>();
	tmp->SetActorLocation(GetActorLocation());
	tmp->SetLifeSpan(_BulletLifetime);
	tmp->_GravityModifier = _BulletGravity;
	tmp->_Velocity = GetActorForwardVector() * _BulletSpeed;
	tmp->Explode = _BulletImpact;

	AudioComponent->Play();

	UGameplayStatics::SpawnEmitterAttached(
		_BulletTrail,
		CastChecked<USceneComponent>(tmp->GetComponentByClass(UStaticMeshComponent::StaticClass())),
		NAME_None,
		GetActorLocation(),
		GetActorRotation(),
		EAttachLocation::KeepWorldPosition,
		false
	);
}

