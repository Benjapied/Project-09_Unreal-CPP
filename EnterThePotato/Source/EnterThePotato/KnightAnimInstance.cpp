#include "KnightAnimInstance.h"

void UKnightAnimInstance::NativeInitializeAnimation()
{
    // Récupère le personnage associé à cet AnimInstance
    APawn* Pawn = TryGetPawnOwner();
    if (Pawn)
    {
        Character = Cast<ACharacter>(Pawn);
    }
}

void UKnightAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if (!Character) return;

    // Récupère la vitesse actuelle du personnage
    FVector Velocity = Character->GetVelocity();
    Speed = Velocity.Size();  // Calcul de la norme du vecteur vitesse

    // Récupère la direction du mouvement
    FRotator Rotation = Character->GetActorRotation();
    Direction = CalculateDirection(Velocity, Rotation);
}
