// Fill out your copyright notice in the Description page of Project Settings.
// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyActorSpawner.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
// Sets default values
AMyActorSpawner::AMyActorSpawner()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	SpawnVolume->SetupAttachment(RootComponent);
}

void AMyActorSpawner::SpawnMyActor()
{
	if (!RotatingObject || !MovingObject || !SpawnVolume)
	{
		UE_LOG(LogTemp, Warning, TEXT("There's no Actor to spawn or BoxComponent!"));
		return;
	}
	//스폰 영역
	FVector BoxExtent = SpawnVolume->GetScaledBoxExtent();
	FVector BoxOrigin = SpawnVolume->GetComponentLocation();

	for (int32 i = 0; i < NumberOfObjects; ++i)
	{
		FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(BoxOrigin, BoxExtent);
		FRotator SpawnRotation = FRotator(0.0f, FMath::RandRange(0, 360), 0.0f); //랜덤으로 Yaw값 조절
		
		//스폰할 액터 선택 변수
		bool bSpawnRotatingObject = FMath::RandBool(); 
		AActor* SpawnedObject = nullptr;

		if (bSpawnRotatingObject)
		{
			//회전 액터 생성
			SpawnedObject = GetWorld()->SpawnActor<ARotatingObject>(RotatingObject, SpawnLocation, SpawnRotation);
			if (SpawnedObject)
			{
				float RandomRotationSpeed = FMath::RandRange(60.0f, 180.0f);
				UE_LOG(LogTemp, Log, TEXT("RotatingObject Spawned: Location(%s), RotationSpeed(%.2f)"), *SpawnLocation.ToString(), RandomRotationSpeed);
				
				ARotatingObject* RObject = Cast<ARotatingObject>(SpawnedObject);
				if (RObject)
				{
					RObject->RotationSpeed = RandomRotationSpeed;
				}
			}
		}
		else
		{
			//움직이는 액터 생성
			SpawnedObject = GetWorld()->SpawnActor<AMovingObject>(MovingObject, SpawnLocation, SpawnRotation);
			if (SpawnedObject)
			{
				float RandomMoveSpeed = FMath::RandRange(100.0f, 300.0f);

				UE_LOG(LogTemp, Log, TEXT("MovingObject Spawned: Location(%s), MoveSpeed(%.2f)"), *SpawnLocation.ToString(), RandomMoveSpeed);

				AMovingObject* MObject = Cast<AMovingObject>(SpawnedObject);
				if (MObject)
				{
					MObject->MoveSpeed = RandomMoveSpeed;
				}
			}
		}
	}
}

// Called when the game starts or when spawned
void AMyActorSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnMyActor();
}



