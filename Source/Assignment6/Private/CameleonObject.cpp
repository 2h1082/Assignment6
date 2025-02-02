// Fill out your copyright notice in the Description page of Project Settings.
// Copyright Epic Games, Inc. All Rights Reserved.

#include "CameleonObject.h"

// Sets default values
ACameleonObject::ACameleonObject()
{
	//SceneRoot ����
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);
	//ù��° ����ƽ �޽� ���� �� ����
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset1(TEXT("/Game/Resources/Props/Floor_400x400.Floor_400x400"));
	if (MeshAsset1.Succeeded())
	{
		Mesh1 = MeshAsset1.Object;
		StaticMeshComp->SetStaticMesh(MeshAsset1.Object);
	}
	//�ι�° ����ƽ �޽� ����
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset2(TEXT("/Game/Resources/Props/SM_Stairs.SM_Stairs"));
	if (MeshAsset2.Succeeded())
	{
		Mesh2 = MeshAsset2.Object;
	}
	//���׸��� ����
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
	//�����ڿ��� �ε� �ȵǾ��� �� �ٽ� ���� �ε�
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
	//3�� Ÿ�̸� ����
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACameleonObject::ChangeMesh, 3.0f, true);
	}
}

void ACameleonObject::ChangeMesh()
{
	if (!Mesh1 || !Mesh2) //�޽� ��ε�
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
	//���� ����
	bUseFirstMesh = !bUseFirstMesh; 
}



