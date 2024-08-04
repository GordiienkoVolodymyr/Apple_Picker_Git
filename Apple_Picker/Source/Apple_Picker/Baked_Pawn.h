#pragma once

#include "AP_GameModeBase.h"
#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Pawn.h"
#include "Containers/Array.h"
#include "NiagaraSystem.h"
#include "Baked_Pawn.generated.h"

UCLASS()
class APPLE_PICKER_API ABaked_Pawn : public APawn
{
	GENERATED_BODY()

public:
	ABaked_Pawn();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Handle_Paddle_Destruction();

	APlayerController* Get_Player_Controller();

protected:
	virtual void BeginPlay() override;
	virtual void PreRegisterAllComponents() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particless Effects")
	UNiagaraSystem* Basket_Particles;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* RootComponent_Basket;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Paddle1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Paddle2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Paddle3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	FVector PaddleOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float Basket_Speed;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	FVector Current_Velocity;

	void Move_Right(float Axis_Value);

	TArray<UStaticMeshComponent*> Paddle_array;

	AAP_GameModeBase* Current_Game_Mode;

	APlayerController* Current_Controller;

};
