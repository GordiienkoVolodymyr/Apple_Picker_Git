// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Apple_Tree_Element_Base.h"
#include "Apple_Base.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Base_Tree.generated.h"

UCLASS()
class APPLE_PICKER_API ABase_Tree : public AApple_Tree_Element_Base
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABase_Tree();
	virtual void Tick(float DeltaTime) override;

	void Start_Spawn_Apple();
	void Start_Redirecting();

	void Stop_Spawn_Apple();
	void Stop_Redirecting();
	void Set_Should_Move(bool Move);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
	UStaticMeshComponent* TreeMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float Movement_Speed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float Outer_Boundary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float Chance_To_Redirect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float Time_Redirect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float Second_Beetwen_Apple_Drops;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float Chance_To_Redirect_Apple_Spawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	TSubclassOf<AApple_Base> Spawn_Obj;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float Internal_Border;

private:

	FTimerHandle ChangedDirectionTimer;
	void ChangedDirection();

	FTimerHandle SpawnAppleTimer;
	void SpawnApple();

	bool Should_Move;
};
