#include "Baked_Pawn.h"
#include "Apple_Base.h"
#include "NiagaraFunctionLibrary.h"

ABaked_Pawn::ABaked_Pawn() :
	PaddleOffset(0.0, 0.0, 150.0)
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent_Basket = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent_Basket"));
	Paddle1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle1"));
	Paddle2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle2"));
	Paddle3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle3"));

	RootComponent = RootComponent_Basket;
	Paddle1->SetupAttachment(RootComponent_Basket);
	Paddle2->SetupAttachment(Paddle1);
	Paddle3->SetupAttachment(Paddle2);
	Basket_Speed = 700.0f;
	Current_Velocity = FVector(0.0f, 0.0f, 0.0f);
	Paddle_array.Push(Paddle1);
	Paddle_array.Push(Paddle2);
	Paddle_array.Push(Paddle3);
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	Current_Game_Mode = nullptr;

	Paddle1->SetNotifyRigidBodyCollision(true);
	Paddle2->SetNotifyRigidBodyCollision(true);
	Paddle3->SetNotifyRigidBodyCollision(true);
	Current_Controller = nullptr;
}

void ABaked_Pawn::BeginPlay()
{
	Super::BeginPlay();
	Paddle1->OnComponentHit.AddDynamic(this, &ABaked_Pawn::OnHit);
	Paddle2->OnComponentHit.AddDynamic(this, &ABaked_Pawn::OnHit);
	Paddle3->OnComponentHit.AddDynamic(this, &ABaked_Pawn::OnHit);
	Current_Game_Mode = Cast<AAP_GameModeBase>(UGameplayStatics::GetGameMode(this));
	Current_Controller = Cast<APlayerController>(GetController());
}

void ABaked_Pawn::PreRegisterAllComponents()
{
	Super::PreRegisterAllComponents();

	Paddle2->SetRelativeLocation(PaddleOffset);
	Paddle3->SetRelativeLocation(PaddleOffset);
}

void ABaked_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (InputEnabled())
	{
		if (!Current_Velocity.IsZero())
		{
			FVector NewLocation = GetActorLocation() + Current_Velocity * DeltaTime;
			SetActorLocation(NewLocation);
		}
	}
}

// Called to bind functionality to input
void ABaked_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move_Right", this, &ABaked_Pawn::Move_Right);

}

void ABaked_Pawn::Handle_Paddle_Destruction()
{
	if (!Paddle_array.IsEmpty())
	{
		UStaticMeshComponent* Pop_Elem = Paddle_array.Pop(true);
		if (Pop_Elem)
		{
			FVector Paddle_Location = Pop_Elem->GetComponentLocation();
			Pop_Elem->DestroyComponent();
			if (Basket_Particles != nullptr && Basket_Particles->IsValid())
			{
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, Basket_Particles, Paddle_Location);
			}
			
		}
	}
}

void ABaked_Pawn::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AApple_Base* Apple_To_Catch = Cast<AApple_Base>(OtherActor);

	if (Apple_To_Catch)
	{
		if (Current_Game_Mode != nullptr)
		{
			Current_Game_Mode->Handle_Apple_Caught();
		}
		OtherActor->Destroy();
	}
}

void ABaked_Pawn::Move_Right(float Axis_Value)
{
	Current_Velocity.Y = FMath::Clamp(Axis_Value, -1.0f, 1.0f) * Basket_Speed;
}

APlayerController* ABaked_Pawn::Get_Player_Controller()
{
	return Current_Controller;
}