// Fill out your copyright notice in the Description page of Project Settings.


#include "SpinningRadar.h"

// Sets default values
ASpinningRadar::ASpinningRadar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set up basic components
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RadarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Radar Mesh"));
	Rotator = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));
	RadarMesh->SetupAttachment(SceneComponent);
	
	//Overwriting the rotation rate of Rotating Movement Component 
	Rotator->RotationRate.Yaw = RotateSpeed;

}

// Called when the game starts or when spawned
void ASpinningRadar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpinningRadar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Detecting hit results and draw the detect line
	FVector StartLoc = GetActorLocation();
	FVector EndLoc = (GetActorForwardVector()*TraceDist)+StartLoc;
	FHitResult HitResult;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, EndLoc, ECC_Visibility);
	DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Orange, false, 0.3f, 0, RadarWaveThickness);

	//Highlight the object that has been hit
	if(bHit)
	{
		auto HitActor = HitResult.GetActor();
		CurrentHitComponent = HitResult.GetComponent();
		CurrentObjectMaterial = HitResult.GetComponent()->GetMaterial(0);
		auto DynamicMaterial = CurrentHitComponent->CreateDynamicMaterialInstance(0,CurrentObjectMaterial);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, HitActor->GetActorLabel());
		DynamicMaterial->SetScalarParameterValue("HighLight", 1.0f);
		CurrentHitComponent->SetMaterial(0, DynamicMaterial);
		FTimerHandle Handle;
		GetWorld()->GetTimerManager().SetTimer(Handle, this, &ASpinningRadar::DeHightLightObject,1.0f, false, 2.0f);
		//DelayTime = 1.0f;
		
	}

}

void ASpinningRadar::DeHightLightObject()
{
		auto DynamicMaterial = CurrentHitComponent->CreateDynamicMaterialInstance(0,CurrentObjectMaterial);
		DynamicMaterial->SetScalarParameterValue("HighLight", 0.0f);
		CurrentHitComponent->SetMaterial(0, DynamicMaterial);
}
