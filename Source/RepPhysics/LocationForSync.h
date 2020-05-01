// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "LocationForSync.generated.h"

/** Compression logic was taken from default UE4 movement replication logic
 * For better documentation please check the following class:
 * Engine\UE4\Source\Runtime\Engine\Classes\Engine\EngineTypes.h : 3148 */

USTRUCT(BlueprintType)
struct FLocationForSync
{
    GENERATED_BODY()

    FLocationForSync();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Location;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRotator Rotation;

    UPROPERTY()
    EVectorQuantization LocationQuantizationLevel;

    UPROPERTY()
    ERotatorQuantization RotationQuantizationLevel;

    bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

    bool SerializeQuantizedVector(FArchive& Ar, FVector& Vector, EVectorQuantization QuantizationLevel);

    bool operator==(const FRepMovement& Other) const
    {
        return (Location == Other.Location) && (Rotation == Other.Rotation);
    }

    bool operator!=(const FRepMovement& Other) const
    {
        return !(*this == Other);
    }
};

template <>
struct TStructOpsTypeTraits<FLocationForSync> : public TStructOpsTypeTraitsBase2<FLocationForSync>
{
    enum
    {
        WithNetSerializer = true
    };
};
