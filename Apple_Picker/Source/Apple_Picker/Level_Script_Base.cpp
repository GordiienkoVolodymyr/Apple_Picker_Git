// Fill out your copyright notice in the Description page of Project Settings.


#include "Level_Script_Base.h"

ALevel_Script_Base::ALevel_Script_Base()
{
	Camera = nullptr;
	Controller = nullptr;
}

void ALevel_Script_Base::BeginPlay()
{
	Super::BeginPlay();

	Controller = GetWorld()->GetFirstPlayerController();

	if (Controller)
	{
		Controller->SetViewTarget(Camera);
	}
}
