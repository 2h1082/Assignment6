// Fill out your copyright notice in the Description page of Project Settings.
// Copyright Epic Games, Inc. All Rights Reserved.

#include "CameleonObject.h"

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
	if (MeshAsset2.Succeeded())
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
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay() Called for %s"), *GetName());
	//생성자에서 로드 안되었을 시 다시 동적 로드
	if (!Mesh1)
	{
		Mesh1 = LoadObject<UStaticMesh>(nullptr, TEXT("/ Game / Resources / Props / Floor_400x400.Floor_400x400"));
	}
	if (!Mesh2)
	{
		Mesh2 = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Resources/Props/SM_Stairs.SM_Stairs"));
	}
	if (!Mesh1 || !Mesh2)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load Mesh1,2"));
		return;
	}
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



