// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "BasicEnemy.generated.h"

UCLASS()
class BULLETHELL_API ABasicEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicEnemy();

	UPROPERTY(EditAnywhere)
		USoundCue* DieSound;

	UPROPERTY(EditAnywhere)
		UAudioComponent* AudioComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* _Mesh;

	UPROPERTY(EditAnywhere)
		float health = 100;

	UPROPERTY(EditAnywhere)
		bool CanTrackPlayer = false;


};
