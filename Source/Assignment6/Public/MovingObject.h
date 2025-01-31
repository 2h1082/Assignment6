// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingObject.generated.h"

UCLASS()
class ASSIGNMENT6_API AMovingObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings");
	UStaticMeshComponent* StaticMeshComp;
	//�̵� �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings");
	float MoveSpeed;
	//�ִ� �̵� �Ÿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings");
	float MaxRange;
	//���� ��ġ
	FVector StartLocation;
	//�̵� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings");
	int32 Direction;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
