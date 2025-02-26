// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"

#include "FactionInterface.h"
#include "Types.h"

#include "Unit.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStopAttacking);

UCLASS()
class ROBOTSVSENGINEERS_API AUnit : public ACharacter, public IFactionInterface
{
	GENERATED_BODY()

	APawn* ATarget = nullptr;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int32 Health;

	// Sets default values for this character's properties
	AUnit();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION(BlueprintCallable, Category=Game)
	virtual UFaction GetFaction() const override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Unit)
	UFaction Faction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Unit)
	FPawnStats Stats;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
	uint8 bIsAttacking : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
	uint8 bIsDead : 1;

	void Die(AActor* DamageCauser);

	UFUNCTION(BlueprintCallable, Category = Game)
	void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(BlueprintAssignable, Category = Unit)
	FStopAttacking StopAttacking;

	UFUNCTION(BlueprintCallable, Category = Unit)
	void AttackFinished();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
	int32 DistanceToTarget;
};
