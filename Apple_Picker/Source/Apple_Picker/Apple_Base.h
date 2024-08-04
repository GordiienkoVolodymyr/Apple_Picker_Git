// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Apple_Tree_Element_Base.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Apple_Base.generated.h"

UCLASS()
class APPLE_PICKER_API AApple_Base : public AApple_Tree_Element_Base
{
	GENERATED_BODY()
	
public:	
	AApple_Base();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* AppleMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particles Effects")
	class UNiagaraSystem* Apple_Destroyed_Particles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float Floor_Boundary;

private:
	class AAP_GameModeBase* Current_Game_Mode;
};
