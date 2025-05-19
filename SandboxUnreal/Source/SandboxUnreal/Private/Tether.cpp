// Fill out your copyright notice in the Description page of Project Settings.


#include "Tether.h"

#include "Components/SplineMeshComponent.h"

// Sets default values
ATether::ATether()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootSceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(rootSceneComponent);
	root = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	root->AttachToComponent(rootSceneComponent, FAttachmentTransformRules::KeepRelativeTransform);

	tetherOrigin = CreateDefaultSubobject<USceneComponent>("TetherOrigin");
	tetherOrigin->AttachToComponent(root, FAttachmentTransformRules::KeepRelativeTransform);

	tethers = TArray<ATether*>();
	connections = TArray<FTetherConnection>();
	
}

// Called when the game starts or when spawned
void ATether::BeginPlay()
{
	Super::BeginPlay();

	GetTethers();
}

void ATether::GetTethers()
{
	TArray<AActor*> ignore = TArray<AActor*>();
	TArray<AActor*> found = TArray<AActor*>();
	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(),
		detectionRadius, TArray<TEnumAsByte<EObjectTypeQuery>>(), ATether::GetClass(),
		ignore, found);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Found actors: " + found.Num());
	
	for (auto actor : found)
	{
		TObjectPtr<ATether> tether = Cast<ATether>(actor);
		if(!IsValid(tether))
		{
			continue;
		}
		
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Actor" + actor->GetActorLabel());

		if (!IsValid(tether->parent))
		{

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, "Invalid tether!" + actor->GetActorLabel());
			tethers.Add(tether);
			tether->parent = this;

			UActorComponent* splineComponent = AddComponentByClass(USplineMeshComponent::StaticClass(), false, root->GetRelativeTransform(), true);
			FinishAndRegisterComponent(splineComponent);
			USplineMeshComponent* spline = Cast<USplineMeshComponent>(splineComponent);

			spline->SetMobility(EComponentMobility::Type::Movable);
			spline->AttachToComponent(root, FAttachmentTransformRules::KeepRelativeTransform);
			spline->SetRelativeLocation(FVector(0, 0, 0));
			
			spline->SetStaticMesh(tetherMesh);
			spline->SetMaterial(0, tetherMaterial);
			
			spline->SetStartPosition(tetherOrigin->GetRelativeLocation());
			spline->SetStartScale(FVector2d(.1f, .1f));
			spline->SetEndPosition(GetTransform().InverseTransformPosition(tether->tetherOrigin->GetComponentLocation()));
			spline->SetEndScale(FVector2d(.1f, .1f));
			
			FTetherConnection* newConnection = new FTetherConnection();
			newConnection->Spline = spline;
			newConnection->Tether = tether;

			connections.Add(*newConnection);
			/*
			*/
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Failed to find actor " + tether->GetActorLabel() + "!");
		}
	}
}

// Called every frame
void ATether::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

