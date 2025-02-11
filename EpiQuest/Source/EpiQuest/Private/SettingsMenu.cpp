// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingsMenu.h"

void USettingsMenu::NativeConstruct() {
    Super::NativeConstruct();
    Slider_MusicVolume->SetValue(MusicSoundClass->Properties.Volume);
    Slider_SoundVolume->SetValue(SoundSoundClass->Properties.Volume);
}

void USettingsMenu::AdjustSoundClassVolume(USoundClass* SoundClass, float Volume)
{
    if (SoundClass)
    {
        SoundClass->Properties.Volume = FMath::Clamp(Volume, 0.0f, 1.0f);
    }
}