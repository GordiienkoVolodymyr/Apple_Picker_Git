#include "Apple_Base.h"
#include "AP_GameModeBase.h"
#include "NiagaraFunctionLibrary.h"

AApple_Base::AApple_Base()
{
	PrimaryActorTick.bCanEverTick = true;
	AppleMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AppleMeshComponent"));

	RootComponent = AppleMeshComponent;
	Floor_Boundary = -700.0f;
	AppleMeshComponent->SetSimulatePhysics(true);

	Current_Game_Mode = nullptr;
}

void AApple_Base::BeginPlay()
{
	Super::BeginPlay();
	
	Current_Game_Mode = Cast<AAP_GameModeBase>(UGameplayStatics::GetGameMode(this));
}

void AApple_Base::Destroyed()
{
	Super::Destroyed();

	if (Apple_Destroyed_Particles != nullptr && Apple_Destroyed_Particles->IsValid())
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, Apple_Destroyed_Particles, GetActorLocation());
	}
}

void AApple_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetActorLocation().Z <= Floor_Boundary)
	{
		if (Current_Game_Mode != nullptr)
		{
			Current_Game_Mode->Handle_Apple_Lost();
		}
		Destroy();
	}
}
