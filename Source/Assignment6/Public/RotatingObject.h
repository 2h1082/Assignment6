// Fill out your copyright notice in the Description page of Project Settings.
// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingObject.generated.h"

UCLASS()
class ASSIGNMENT6_API ARotatingObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotatingObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings");
	UStaticMeshComponent* StaticMeshComp;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//ȸ�� �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings");
	float RotationSpeed;
};
