
#include "Base_Tree.h"

ABase_Tree::ABase_Tree()
{
	PrimaryActorTick.bCanEverTick = true;

	TreeMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TreeMeshComponent"));
	RootComponent = TreeMeshComponent;
	Movement_Speed = 550.0f;
	Outer_Boundary = 900.0f;
	Chance_To_Redirect = 0.4f;
	Time_Redirect = 1.0f;
	Second_Beetwen_Apple_Drops = 1.0f;
	Chance_To_Redirect_Apple_Spawn = 0.5f;
	Internal_Border = 600.0f;
	Should_Move = false;
}

void ABase_Tree::BeginPlay()
{
	Super::BeginPlay();
}

void ABase_Tree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Should_Move)
	{
		FVector TempLocation = GetActorLocation();

		if (TempLocation.Y >= Outer_Boundary)
		{
			Movement_Speed = -(FMath::Abs(Movement_Speed));
		}
		else if (TempLocation.Y <= -Outer_Boundary)
		{
			Movement_Speed = FMath::Abs(Movement_Speed);
		}
		TempLocation.Y += Movement_Speed * DeltaTime;
		SetActorLocation(TempLocation);
	}
}

void ABase_Tree::ChangedDirection()
{
	if (Should_Move)
	{
		FVector TempLocation = GetActorLocation();
		if (TempLocation.Y >= Internal_Border && TempLocation.Y >= -Internal_Border)
		{
			if (FMath::FRand() <= Chance_To_Redirect)
			{
				Movement_Speed = Movement_Speed * -1.0f;
			}
		}
	}
}

void ABase_Tree::SpawnApple()
{
	FVector Spawn_Apple_Location = GetActorLocation();
	FRotator Spawn_Rotator = GetActorRotation();

	if (FMath::FRand() <= Chance_To_Redirect_Apple_Spawn)
	{
		Spawn_Apple_Location.Y -= 150.0f;
	}
	else
	{
		Spawn_Apple_Location.Y += 150.0f;
	}

	GetWorld()->SpawnActor<AApple_Base>(Spawn_Obj, Spawn_Apple_Location, Spawn_Rotator);
}

void ABase_Tree::Start_Spawn_Apple()
{
	GetWorld()->GetTimerManager().SetTimer(SpawnAppleTimer, this, &ABase_Tree::SpawnApple, Second_Beetwen_Apple_Drops, true);
}

void ABase_Tree::Start_Redirecting()
{
	GetWorld()->GetTimerManager().SetTimer(ChangedDirectionTimer, this, &ABase_Tree::ChangedDirection, Time_Redirect, true);
}

void ABase_Tree::Stop_Spawn_Apple()
{
	GetWorld()->GetTimerManager().ClearTimer(SpawnAppleTimer);
}

void ABase_Tree::Stop_Redirecting()
{
	GetWorld()->GetTimerManager().ClearTimer(ChangedDirectionTimer);
}

void ABase_Tree::Set_Should_Move(bool Move)
{
	Should_Move = Move;
}