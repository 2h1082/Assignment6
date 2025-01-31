// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingObject.h"

// Sets default values
AMovingObject::AMovingObject()
{
	PrimaryActorTick.bCanEverTick = true;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);
	//����ƽ �޽� ����
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_AssetPlatform.SM_AssetPlatform"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}
	//���׸��� ����
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Concrete_Grime"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Fail"));
	}
	SetActorRotation(FRotator(0.0f, 0.0f, 0.0f)); //ȸ��
	SetActorScale3D(FVector(2.0f)); //ũ��
	
	MoveSpeed = 200.0f;
	StartLocation=GetActorLocation();
	MaxRange = 400.0f;
	Direction = 1;
}

// Called when the game starts or when spawned
void AMovingObject::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMovingObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//���� ��ġ
	FVector CurrentLocation = GetActorLocation();
	//�̵� �Ÿ�
	float Distance = MoveSpeed * DeltaTime * Direction;
	//��ġ ���
	FVector NextLocation = CurrentLocation + FVector(0.0f, Distance,0.0f);
	if (FMath::Abs(NextLocation.Y-StartLocation.Y)>=MaxRange)
	{
		Direction *= -1; //�̵� ���� ����
	}
	//��ġ ������Ʈ
	SetActorLocation(NextLocation);
}

