// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraActor.h"
#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Level_Script_Base.generated.h"


UCLASS()
class APPLE_PICKER_API ALevel_Script_Base : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	ALevel_Script_Base();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Setup")
	class ACameraActor* Camera;

private:
	class APlayerController* Controller;
};
