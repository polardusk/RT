// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReplicatedTest.generated.h"

UCLASS()
class RT_API AReplicatedTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AReplicatedTest();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated, ReplicatedUsing = OnRep_IsOn)
	bool bIsOn;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* BoxTrigger;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult); 

	UFUNCTION()
	void OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex); 

	UFUNCTION()
	void OnRep_IsOn(bool bOldValue);

};
