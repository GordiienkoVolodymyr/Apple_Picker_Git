#include "AP_GameModeBase.h"
#include "Baked_Pawn.h"
#include "Apple_Base.h"
#include "Base_Tree.h"

void AAP_GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (Game_Widget_type)
	{
		Widget = Cast<UAP_Base_Widget>(CreateWidget(GetWorld(), Game_Widget_type));

		if (Widget)
		{
			Widget->AddToViewport();
			Update_Widget_Text();
		}
	}

	Basket_ptr = Cast<ABaked_Pawn>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (Basket_ptr)
	{
		Basket_ptr->DisableInput(nullptr);
	}

	FTimerHandle Timer_Game_Start;
	GetWorld()->GetTimerManager().SetTimer(Timer_Game_Start, this, &AAP_GameModeBase::Handle_Game_Start, Game_Start_Delay, false);
}

void AAP_GameModeBase::Handle_Apple_Lost()
{
	Apple_Lost = Apple_Lost + 1;
	UE_LOG(LogTemp, Warning, TEXT("Apple Lost"));
	UE_LOG(LogTemp, Warning, TEXT(" Total Apple Lost: %d"), Apple_Lost);

	if (Basket_ptr != nullptr)
	{
		Basket_ptr->Handle_Paddle_Destruction();
	}

	if (Apple_Lost >= Apple_To_Lose)
	{
		Handle_Game_Over(false);
		if (Widget)
		{
			Widget->Set_Game_Over(false);
		}
	}
}

void AAP_GameModeBase::Handle_Apple_Caught()
{
	Apple_Caught = Apple_Caught + 1;
	Update_Widget_Text();
	UE_LOG(LogTemp, Warning, TEXT("Apple Caught"));
	UE_LOG(LogTemp, Warning, TEXT(" Total Apple Caught: %d"), Apple_Caught);

	if (Apple_Caught >= Apple_To_Won)
	{
		Handle_Game_Over(true);
	}

}

float AAP_GameModeBase::Get_Time_Start_Game() const
{
	return Game_Start_Delay;
}

void AAP_GameModeBase::Handle_Game_Over_Implementation(bool Game_Won)
{
	TArray<AActor*> Found_Apple_Tree_Element;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AApple_Tree_Element_Base::StaticClass(), Found_Apple_Tree_Element);
	for (AActor* TreeFound : Found_Apple_Tree_Element)
	{

		if (ABase_Tree* Temp_Ptr_Tree = Cast<ABase_Tree>(TreeFound))
		{
			Temp_Ptr_Tree->Stop_Spawn_Apple();
			Temp_Ptr_Tree->Stop_Redirecting();
			Temp_Ptr_Tree->Set_Should_Move(false);
		}
		else if (AApple_Base* Temp_Ptr_Apple = Cast<AApple_Base>(TreeFound))
		{
			Temp_Ptr_Apple->Destroy();
		}
	}

	if (Basket_ptr && Basket_ptr->Get_Player_Controller())
	{
		Basket_ptr->DisableInput(Basket_ptr->Get_Player_Controller());
		Basket_ptr->SetActorTickEnabled(false);
	}

	if (Widget)
	{
		Widget->Set_Game_Over(Game_Won);
	}
}


void AAP_GameModeBase::Handle_Game_Start()
{
	TArray<AActor*> Found_Apple_Tree_Element;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AApple_Tree_Element_Base::StaticClass(), Found_Apple_Tree_Element);
	for (AActor* TreeFound : Found_Apple_Tree_Element)
	{

		if (ABase_Tree* Temp_Ptr_Tree = Cast<ABase_Tree>(TreeFound))
		{
			Temp_Ptr_Tree->Start_Spawn_Apple();
			Temp_Ptr_Tree->Start_Redirecting();
			Temp_Ptr_Tree->Set_Should_Move(true);
		}
	}

	if (Basket_ptr && Basket_ptr->Get_Player_Controller())
	{
		Basket_ptr->EnableInput(Basket_ptr->Get_Player_Controller());
		Basket_ptr->SetActorTickEnabled(true);
	}


}

void AAP_GameModeBase::Update_Widget_Text()
{
	if (Widget)
	{
		Widget->Set_Apple_Collected(Apple_Caught, Apple_To_Won);
	}
}

