// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#pragma once

#include <vdtreflect/runtime.h>

template <>
struct EnumType<enum class TestEnum>
{
    static const char* name();
    static const std::map<const char*, int> values();
};

template <>
struct EnumType<enum class ApplicationMode>
{
    static const char* name();
    static const std::map<const char*, int> values();
};

struct FooType : RegisteredInTypeFactory<FooType>
{
    FooType() = delete;

    static const Type& type();
    static bool registered() { return value; };
};

struct PooType : RegisteredInTypeFactory<PooType>
{
    PooType() = delete;

    static const Type& type();
    static bool registered() { return value; };
};

