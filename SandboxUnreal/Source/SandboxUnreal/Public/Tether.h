// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TetherConnection.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Tether.generated.h"

UCLASS()
class SANDBOXUNREAL_API ATether : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATether();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double detectionRadius = 600;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* rootSceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<ATether*> tethers;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FTetherConnection> connections;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ATether* parent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBoxComponent* root;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMesh* tetherMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterial* tetherMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* tetherOrigin;

	void GetTethers();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ConnectTether(ATether* newChild);
};
