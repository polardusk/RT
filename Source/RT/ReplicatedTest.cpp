// Fill out your copyright notice in the Description page of Project Settings.


#include "ReplicatedTest.h"
#include "Components/BoxComponent.h"
#include "Net/UnrealNetwork.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AReplicatedTest::AReplicatedTest()
{
	bReplicates = true;
	BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));
	BoxTrigger->SetupAttachment(RootComponent);
}

void AReplicatedTest::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AReplicatedTest, bIsOn);
}

// Called when the game starts or when spawned
void AReplicatedTest::BeginPlay()
{
	Super::BeginPlay();
	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &AReplicatedTest::OnBoxOverlapBegin);
	BoxTrigger->OnComponentEndOverlap.AddDynamic(this, &AReplicatedTest::OnBoxOverlapEnd);
}

void AReplicatedTest::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* OtherPawn = Cast<APawn>(OtherActor);
	if (!IsValid(OtherPawn))
	{
		return;
	}

	if (!OtherComp->IsA<UCapsuleComponent>())
	{
		return;
	}

	if (HasAuthority())
	{
		bIsOn = true;
		// TODO add check when single player
	}
	else if (OtherPawn->IsLocallyControlled())
	{
		bIsOn = true;
		OnRep_IsOn(false);
	}
}

void AReplicatedTest::OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APawn* OtherPawn = Cast<APawn>(OtherActor);
	if (!IsValid(OtherPawn))
	{
		return;
	}

	if (!OtherComp->IsA<UCapsuleComponent>())
	{
		return;
	}

	if (HasAuthority())
	{
		bIsOn = false;
	}
	else if (OtherPawn->IsLocallyControlled())
	{
		bIsOn = false;
		OnRep_IsOn(true);
	}
}

void AReplicatedTest::OnRep_IsOn(bool bOldValue)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT("Current value: %i"), bIsOn));
}

