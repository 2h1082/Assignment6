// Fill out your copyright notice in the Description page of Project Settings.
// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameleonObject.generated.h"

UCLASS()
class ASSIGNMENT6_API ACameleonObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameleonObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings");
	UStaticMeshComponent* StaticMeshComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings");
	UStaticMesh* Mesh1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings");
	UStaticMesh* Mesh2;
	//��� ���� �޽� ���� Ȯ�� ����
	bool bUseFirstMesh = true;
	//Ÿ�̸� �ڵ� ����
	FTimerHandle TimerHandle;
public:	
	void ChangeMesh();
	

};
