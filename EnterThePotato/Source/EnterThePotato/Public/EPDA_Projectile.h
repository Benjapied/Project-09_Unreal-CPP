#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EPDA_Projectile.generated.h"

UCLASS()
class ENTERTHEPOTATO_API UEPDA_Projectile : public UDataAsset
{
	GENERATED_BODY()
	
protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile Settings")
    UStaticMesh* ProjectileMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile Settings")
    float InitialSpeed = 800;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile Settings")
    float MaxSpeed = 8500;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile Settings")
    float GravityScale = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile Settings")
    float Damage = 10.f;

public:

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Projectile Settings")
    UStaticMesh* GetProjectileMesh() const { return ProjectileMesh; }


    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Projectile Settings")
    float GetInitialSpeed() const { return InitialSpeed; }


    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Projectile Settings")
    float GetMaxSpeed() const { return MaxSpeed; }


    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Projectile Settings")
    float GetGravityScale() const { return GravityScale; }

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Projectile Settings")
    float GetDamage() const { return Damage; }
};
