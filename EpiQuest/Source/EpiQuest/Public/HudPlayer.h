// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "HudPlayer.generated.h"

/**
 * 
 */
UCLASS()
class EPIQUEST_API UHudPlayer : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* TextRepearedRobot;
};
