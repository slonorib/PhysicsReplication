// Fill out your copyright notice in the Description page of Project Settings.


#include "LocationForSync.h"

FLocationForSync::FLocationForSync() :
    Location(FVector::ZeroVector),
    Rotation(FRotator::ZeroRotator),
    LocationQuantizationLevel(EVectorQuantization::RoundWholeNumber),
    RotationQuantizationLevel(ERotatorQuantization::ByteComponents)
{
}

bool FLocationForSync::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
    bOutSuccess &= SerializeQuantizedVector(Ar, Location, LocationQuantizationLevel);
    switch (RotationQuantizationLevel)
    {
    case ERotatorQuantization::ByteComponents:
        {
            Rotation.SerializeCompressed(Ar);
            break;
        }

    case ERotatorQuantization::ShortComponents:
        {
            Rotation.SerializeCompressedShort(Ar);
            break;
        }
    }

    return true;
}

bool FLocationForSync::SerializeQuantizedVector(FArchive& Ar, FVector& Vector, EVectorQuantization QuantizationLevel)
{
    switch (QuantizationLevel)
    {
    case EVectorQuantization::RoundTwoDecimals:
        {
            return SerializePackedVector<100, 30>(Vector, Ar);
        }

    case EVectorQuantization::RoundOneDecimal:
        {
            return SerializePackedVector<10, 27>(Vector, Ar);
        }

    default:
        {
            return SerializePackedVector<1, 24>(Vector, Ar);
        }
    }
}
