// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "SpinningRadar.generated.h"

UCLASS()
class UECPP_PRACTICE_API ASpinningRadar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpinningRadar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, Category="Spinning Radar")
	float TraceDist = 1000.0f;


	
	
	UPROPERTY(EditAnywhere, Category="Spinning Radar")
	float RadarWaveThickness = 1.5f;

	UPROPERTY(EditAnywhere, Category="Spinning Radar")
	UStaticMeshComponent* RadarMesh;

	URotatingMovementComponent* Rotator;

	UFUNCTION()
	void DeHightLightObject();
	
	UMaterialInterface* CurrentObjectMaterial = nullptr;
	
	UPrimitiveComponent* CurrentHitComponent = nullptr;
	
	float DelayTime = 2.0f;

	float RotateSpeed = 90.0f;

	FRotator RotateRate = {1,0,1};

	
private:
	class USceneComponent* SceneComponent;
};
