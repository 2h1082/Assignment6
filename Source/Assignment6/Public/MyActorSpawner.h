// Fill out your copyright notice in the Description page of Project Settings.
// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "RotatingObject.h"
#include "MovingObject.h"
#include "CameleonObject.h"
#include "MyActorSpawner.generated.h"

UCLASS()
class ASSIGNMENT6_API AMyActorSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActorSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//스폰 영역
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Settings");
	class UBoxComponent* SpawnVolume;
	//스폰할 액터1
	UPROPERTY(EditAnywhere, Category = "Spawn Settings");
	TSubclassOf<ARotatingObject> RotatingObject;
	//스폰할 액터2
	UPROPERTY(EditAnywhere, Category = "Spawn Settings");
	TSubclassOf<AMovingObject> MovingObject;
	//스폰할 액터3
	UPROPERTY(EditAnywhere, Category = "Spawn Settings");
	TSubclassOf<ACameleonObject> CameleonObject;
	//스폰 개수
	UPROPERTY(EditAnywhere, Category = "Spawn Settings");
	int32 NumberOfObjects = 15;

public:	
	//스폰 함수
	UFUNCTION()
	void SpawnMyActor();

};
