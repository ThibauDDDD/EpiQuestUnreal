// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Sound/SoundMix.h"
#include "Sound/SoundClass.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Slider.h"

#include "SettingsMenu.generated.h"

/**
 * 
 */
UCLASS()
class EPIQUEST_API USettingsMenu : public UUserWidget
{
	GENERATED_BODY()

public:
    UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
    class USlider* Slider_MusicVolume;
    UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
    class USlider* Slider_SoundVolume;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    USoundClass* MusicSoundClass;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    USoundClass* SoundSoundClass;

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void AdjustSoundClassVolume(USoundClass* SoundClass, float Volume);

protected:
    virtual void NativeConstruct() override;
};
