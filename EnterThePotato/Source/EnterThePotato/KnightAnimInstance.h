#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KnightAnimInstance.generated.h"

UCLASS()
class ENTERTHEPOTATO_API UKnightAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

public:
    // Vitesse actuelle du personnage
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
    float Speed;

    // Direction du mouvement
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
    float Direction;

    // Référence au personnage
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
    ACharacter* Character;

    // Fonction appelée à chaque frame
    virtual void NativeInitializeAnimation() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
