// Fill out your copyright notice in the Description page of Project Settings.


#include "EP_HealingCollectible.h"
#include "../EnterThePotatoCharacter.h"

void AEP_HealingCollectible::OnCollect(AActor* actor) {

	AEnterThePotatoCharacter* obj = Cast<AEnterThePotatoCharacter>(actor);

	if (obj) {

		obj->SetHealth(obj->GetMaxHealth());
		Destroy();
	}

}