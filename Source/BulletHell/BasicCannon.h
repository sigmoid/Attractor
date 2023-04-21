// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "BasicCannon.generated.h"

UCLASS()
class BULLETHELL_API ABasicCannon : public AActor
{
	GENERATED_BODY()

public:
	ABasicCannon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Fire();

	UPROPERTY(EditAnywhere)
	UParticleSystem* _BulletTrail;

	UPROPERTY(EditAnywhere)
		UParticleSystem* _BulletImpact;

	UPROPERTY(EditAnywhere)
		USoundCue* ShotSound;

	UPROPERTY(EditAnywhere)
		UAudioComponent* AudioComponent;

private:
	UPROPERTY(EditAnywhere)
		float _FireRate = 1;
	UPROPERTY(EditAnywhere)
		float _BulletGravity = 100000000;
	UPROPERTY(EditAnywhere)
		float _BulletSpeed;
	UPROPERTY(EditAnywhere)
		float _BulletLifetime;

	/* The mesh component */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* ShipMeshComponent;

	float _Timer;

	
	
	
};
