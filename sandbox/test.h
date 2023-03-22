// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "test_generated.h"

using namespace reflect;

namespace math
{
	struct vec3
	{
		float x{ 0.f }, y{ 0.f }, z{ 0.f };
	};
}

ENUM(Category = MyEnums)
enum class TestEnum
{
	A,
	B = 2
};

CLASS(Category = MyClass, Serializable = true)
class Foo : public IType
{
public:
	Foo() = default;
	virtual ~Foo() = default;

	PROPERTY(JsonExport = true) int m_int{ 4 };
	PROPERTY() TestEnum m_enum = TestEnum::A;
	PROPERTY() bool m_bool = false;
	PROPERTY() std::string m_string = "foo";
	PROPERTY() std::list<int> list;
	PROPERTY() std::map<std::string, int> dictionary;
	PROPERTY() math::vec3 position;

	GENERATED_BODY()
};

CLASS()
class Poo : public Foo
{
public:
	PROPERTY() int c = 15;
	PROPERTY() std::tuple<int, float, bool, double> tuple;
	PROPERTY() std::map<std::string, std::vector<int>> power_dictionary;
	PROPERTY() std::vector<std::shared_ptr<Foo>> shared_foos;
	PROPERTY() std::vector<std::unique_ptr<Foo>> unique_foos;	
	PROPERTY() Foo type;
	PROPERTY() std::shared_ptr<Foo> s_type;
	PROPERTY() std::unique_ptr<Foo> u_type;

	GENERATED_BODY()
};

ENUM()
enum class ApplicationMode : int
{
	Editor = 0,
	Server = 1,
	Standalone = 2,
};