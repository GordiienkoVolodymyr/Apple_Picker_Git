// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AP_Base_Widget.generated.h"

/**
 * 
 */
UCLASS()
class APPLE_PICKER_API UAP_Base_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintImplementableEvent)
	void Set_Apple_Collected(int Apples_Collected, int Apples_Lost);

	UFUNCTION(BlueprintImplementableEvent)
	void Set_Game_Over(bool Won);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float Game_Start_Delay = 5.0f;
};
