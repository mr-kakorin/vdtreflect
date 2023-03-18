// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#pragma once

#include <vdtreflect/runtime.h>

template <>
struct reflect::Enum<enum class TestEnum> : reflect::RegisteredInEnumFactory<enum class TestEnum>
{
    static const char* const name();
    static const reflect::enum_values_t& values();
    
    static bool registered() { return value; };
};

template <>
struct reflect::Enum<enum class ApplicationMode> : reflect::RegisteredInEnumFactory<enum class ApplicationMode>
{
    static const char* const name();
    static const reflect::enum_values_t& values();
    
    static bool registered() { return value; };
};

template <>
struct reflect::Type<class Foo> : reflect::RegisteredInTypeFactory<class Foo>
{
    static const reflect::meta_t& meta();
    static const char* const name();
    static const reflect::properties_t& properties();

    static bool registered() { return value; };
};

template <>
struct reflect::Type<class Poo> : reflect::RegisteredInTypeFactory<class Poo>
{
    static const reflect::meta_t& meta();
    static const char* const name();
    static const reflect::properties_t& properties();

    static bool registered() { return value; };
};

template <>
struct reflect::Type<struct Too> : reflect::RegisteredInTypeFactory<struct Too>
{
    static const reflect::meta_t& meta();
    static const char* const name();
    static const reflect::properties_t& properties();

    static bool registered() { return value; };
};

