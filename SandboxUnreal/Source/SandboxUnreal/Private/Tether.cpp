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

	ignore.Add(this);
	
	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(),
		detectionRadius, TArray<TEnumAsByte<EObjectTypeQuery>>(), ATether::GetClass(),
		ignore, found);

	ATether* finalTether = nullptr;
	for (auto actor : found)
	{
		TObjectPtr<ATether> tether = Cast<ATether>(actor);
		if(!IsValid(tether))
		{
			continue;
		}
		else if(tether == parent)
		{
			continue;
		}

		if(!IsValid(finalTether))
		{
			finalTether = tether;
			continue;
		}
		else
		{
			double currentDistance = FVector::Distance(GetActorLocation(), finalTether->GetActorLocation());
			double newDistance = FVector::Distance(GetActorLocation(), tether->GetActorLocation());

			if(currentDistance > newDistance)
			{
				finalTether = tether;
			}
		}
	}

	if(IsValid(finalTether))
	{
		if (!IsValid(finalTether->parent))
		{
			ConnectTether(finalTether);
		}
		else
		{
			// This may cause problems if (this) already has a parent
			finalTether->ConnectTether(this);
		}
	}
}

void ATether::ConnectTether(ATether* newChild)
{
	tethers.Add(newChild);
	newChild->parent = this;

	UActorComponent* splineComponent = AddComponentByClass(USplineMeshComponent::StaticClass(), false, root->GetRelativeTransform(), true);
	FinishAndRegisterComponent(splineComponent);
	USplineMeshComponent* spline = Cast<USplineMeshComponent>(splineComponent);

	spline->SetMobility(EComponentMobility::Type::Movable);
	spline->AttachToComponent(root, FAttachmentTransformRules::KeepRelativeTransform);
	spline->SetRelativeLocation(FVector(0, 0, 0));
			
	spline->SetStaticMesh(tetherMesh);
	spline->SetMaterial(0, tetherMaterial);

	FVector startPosition = tetherOrigin->GetRelativeLocation();
	FVector endPosition = spline->GetComponentTransform().InverseTransformPosition(newChild->tetherOrigin->GetComponentLocation());
	FVector directionNormalized = (endPosition - startPosition);
	directionNormalized.Normalize();
			
	spline->SetStartPosition(startPosition);
	spline->SetStartScale(FVector2d(.1f, .1f));
	spline->SetStartTangent(directionNormalized * 100);
			
	spline->SetEndPosition(endPosition);
	spline->SetEndScale(FVector2d(.1f, .1f));
	spline->SetEndTangent(directionNormalized * 100);
			
	FTetherConnection* newConnection = new FTetherConnection();
	newConnection->Spline = spline;
	newConnection->Tether = newChild;

	connections.Add(*newConnection);
}

// Called every frame
void ATether::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

