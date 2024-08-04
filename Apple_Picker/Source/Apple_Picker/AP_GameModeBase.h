#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "AP_Base_Widget.h"
#include "AP_GameModeBase.generated.h"


UCLASS()
class APPLE_PICKER_API AAP_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	void Handle_Apple_Lost();
	void Handle_Apple_Caught();

	UFUNCTION(BlueprintCallable)
	float Get_Time_Start_Game() const;

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
	void Handle_Game_Over(bool Game_Won);

	UPROPERTY(EditAnywhere, Category = "Setup")
	int32 Apple_To_Won = 10;

	UPROPERTY(EditAnywhere, Category = "Setup")
	int32 Apple_To_Lose = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float Game_Start_Delay = 5.0f;

	// To specify widget blueprint/type in Editor
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UUserWidget> Game_Widget_type;

	UPROPERTY()
	UAP_Base_Widget* Widget;

private:
	int32 Apple_Lost = 0;
	int32 Apple_Caught = 0;

	class ABaked_Pawn* Basket_ptr = nullptr;

	void Handle_Game_Start();

	void Update_Widget_Text();
};
