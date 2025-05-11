// Fill out your copyright notice in the Description page of Project Settings.


#include "Tether.h"

// Sets default values
ATether::ATether()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	root = CreateDefaultSubobject<UBoxComponent>("Root");
	SetRootComponent(root);

	detector = CreateDefaultSubobject<USphereComponent>(TEXT("Detector"));
	detector->SetupAttachment(root);
	detector->InitSphereRadius(600.0f);
	detector->SetGenerateOverlapEvents(true);
	detector->SetSimulatePhysics(false);
	detector->SetCollisionObjectType(ECC_WorldDynamic);
	detector->CanCharacterStepUpOn = ECB_No;
	detector->SetActive(false);
	
}

// Called when the game starts or when spawned
void ATether::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> actors;
	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), detector->GetComponentLocation(),
		detector->GetScaledSphereRadius(), TArray<TEnumAsByte<EObjectTypeQuery>>(), ATether::GetClass(),
		TArray<AActor*>(), actors);
	
	UE_LOG(LogTemp, Display, TEXT("List length: %d"), actors.Num());
	for (auto actor : actors)
	{
		UE_LOG(LogTemp, Display, TEXT("Actor %s"), *actor->GetActorLabel());
	}
}

// Called every frame
void ATether::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

