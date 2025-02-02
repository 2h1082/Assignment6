// Fill out your copyright notice in the Description page of Project Settings.
// Copyright Epic Games, Inc. All Rights Reserved.

#include "CameleonObject.h"

FTimerHandle TimerHandle;
// Sets default values
ACameleonObject::ACameleonObject()
{
	//SceneRoot 설정
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);
	//첫번째 스태틱 메시 저장 및 설정
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset1(TEXT("/Game/Resources/Props/Floor_400x400.Floor_400x400"));
	if (MeshAsset1.Succeeded())
	{
		Mesh1 = MeshAsset1.Object;
		StaticMeshComp->SetStaticMesh(MeshAsset1.Object);
	}
	//두번째 스태틱 메시 저장
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset2(TEXT("/Game/Resources/Props/SM_Stairs.SM_Stairs"));
	if (MeshAsset1.Succeeded())
	{
		Mesh2 = MeshAsset2.Object;
	}
	//메테리얼 설정
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Brick_Clay_New.M_Brick_Clay_New"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}
}

// Called when the game starts or when spawned
void ACameleonObject::BeginPlay()
{
	Super::BeginPlay();
	//3초 타이머 설정
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACameleonObject::ChangeMesh, 3.0f, true);
	}
}

void ACameleonObject::ChangeMesh()
{
	if (!Mesh1 || !Mesh2) //메쉬 언로드
	{
		return; 
	}
	if (bUseFirstMesh)
	{
		StaticMeshComp->SetStaticMesh(Mesh2);
	}
	else
	{
		StaticMeshComp->SetStaticMesh(Mesh1);
	}
	//상태 변경
	bUseFirstMesh = !bUseFirstMesh; 
}



