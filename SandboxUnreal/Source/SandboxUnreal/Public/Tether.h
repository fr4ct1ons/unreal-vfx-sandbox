// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USphereComponent* detector;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBoxComponent* root;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
