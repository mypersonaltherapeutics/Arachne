#pragma once

#include <random>       // mt19937, mt19937_64
#include <stdint.h>     // uint8_t

#include <mat.h>
#include <mpi.h>

#include "DistEnv.h"    // MPI_MT19937, MPI_MT19937_64


// Get Matlab class ID inlined utils

template <typename T>
inline mxClassID GetMxClassId()
{
    return mxUNKNOWN_CLASS;
}

template <>
inline mxClassID GetMxClassId<float>()
{
    return mxSINGLE_CLASS;
}

template <>
inline mxClassID GetMxClassId<double>()
{
    return mxDOUBLE_CLASS;
}

template <>
inline mxClassID GetMxClassId<int>()
{
    return mxINT32_CLASS;
}

template <>
inline mxClassID GetMxClassId<uint8_t>()
{
    return mxUINT8_CLASS;
}

template <>
inline mxClassID GetMxClassId<bool>()
{
    return mxLOGICAL_CLASS;
}


// Get MPI type inlined utils

template <typename T>
inline MPI_Datatype GetMpiDataType()
{
    return MPI_Datatype(-1);
}

template <>
inline MPI_Datatype GetMpiDataType<float>()
{
    return MPI_FLOAT;
}

template <>
inline MPI_Datatype GetMpiDataType<double>()
{
    return MPI_DOUBLE;
}

template <>
inline MPI_Datatype GetMpiDataType<int>()
{
    return MPI_INT;
}

template <>
inline MPI_Datatype GetMpiDataType<uint8_t>()
{
    return MPI_BYTE;
}

template <>
inline MPI_Datatype GetMpiDataType<bool>()
{
    return MPI_BYTE;
}

template <>
inline MPI_Datatype GetMpiDataType<std::mt19937>()
{
    return DistEnv::MPI_MT19937;
}

template <>
inline MPI_Datatype GetMpiDataType<std::mt19937_64>()
{
    return DistEnv::MPI_MT19937_64;
}