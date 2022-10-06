/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <cstring>
#include <functional>
#include <map>
#include <memory>
#include <string>

template <typename T>
struct EnumType
{
	static const char* name() { return ""; }
	static const std::map<const char*, int> values() {
		static std::map<const char*, int> s_values;
		return s_values;
	}
};

template <class T>
std::string enumToString(const T t)
{
	const int value = static_cast<int>(t);
	for (const auto& pair : EnumType<T>::values())
	{
		if (pair.second == value)
		{
			return pair.first;
		}
	}
	return "";
}

template <class T>
bool stringToEnum(const char* name, T& t)
{
	for (const auto& pair : EnumType<T>::values())
	{
		if (std::strcmp(pair.first, name) == 0)
		{
			return t = static_cast<T>(pair.second), true;
		}
	}
	return false;
}

template <class T>
bool stringToEnum(const std::string& name, T& t)
{
	for (const auto& pair : EnumType<T>::values())
	{
		if (name == pair.first)
		{
			return t = static_cast<T>(pair.second), true;
		}
	}
	return false;
}

typedef unsigned long long member_address_t;

enum class NativeType
{
	NT_invalid,
	NT_bool,
	NT_char,
	NT_double,
	NT_enum,
	NT_float,
	NT_int,
	NT_string,
	NT_void
};

typedef std::map<std::string, std::string> meta_t;

struct Property
{
	Property(const std::string& name, const NativeType type, const std::string& typeStr, const std::size_t size, const member_address_t address, const meta_t& meta)
		: name(name)
		, type(type)
		, typeStr(typeStr)
		, size(size)
		, address(address)
		, meta(meta)
	{

	}

	const std::string name;
	const NativeType type{ NativeType::NT_invalid };
	const std::string typeStr;
	const std::size_t size;
	const member_address_t address{ 0 };
	const meta_t meta;

	template<typename T>
	T& value() const
	{
		return *reinterpret_cast<T*>(address);
	}
};
typedef std::map<std::string, Property> properties_t;

struct IType
{
	IType() = default;
	virtual ~IType() = default;

	virtual const std::string& getTypeName() const = 0;
	virtual const meta_t& getTypeMeta() const = 0;
	virtual const properties_t getTypeProperties() const = 0;
	virtual std::size_t getTypeSize() const = 0;
};
typedef std::function<IType* ()> factory_constructor_t;
typedef std::function<IType* ()> type_constructor_t;
typedef std::function<const meta_t& ()> factory_meta_t;

struct Type
{
	Type(const type_constructor_t& constructor, const std::string& name, const meta_t& meta, const std::size_t size)
		: constructor(constructor)
		, name(name)
		, meta(meta)
		, size(size)
	{}

	type_constructor_t constructor;
	std::string name;
	meta_t meta;
	std::size_t size;
};

class TypeFactory final
{
public:
	TypeFactory() = delete;

	static IType* instantiate(const std::string& name)
	{
		const auto& it = collection().find(name);
		if (it != collection().end())
		{
			return it->second.constructor();
		}
		return nullptr;
	}

	template <typename T>
	static T* instantiate()
	{
		return reinterpret_cast<T*>(instantiate(Type<T>::name()));
	}

	template <typename T>
	static T* instantiate(const std::string& name)
	{
		return reinterpret_cast<T*>(instantiate(name));
	}

	static std::vector<std::string> list()
	{
		std::vector<std::string> result;
		for (const auto& [typeName, type] : collection())
		{
			result.push_back(typeName);
		}
		return result;
	}

	static std::vector<std::string> list(const std::string& metaOption)
	{
		return TypeFactory::list(metaOption, "");
	}

	static std::vector<std::string> list(const std::string& metaOption, const std::string& metaValue)
	{
		std::vector<std::string> result;
		for (const auto& [typeName, type] : collection())
		{
			const auto& it = type.meta.find(metaOption);
			if (it != type.meta.end() && (metaValue.empty() || it->second == metaValue))
			{
				result.push_back(typeName);
			}
		}
		return result;
	}

	static bool registerType(const Type& type)
	{
		collection().insert(std::make_pair(type.name, type));
		return true;
	}

private:
	static std::map<std::string, Type>& collection()
	{
		static std::map<std::string, Type> s_types;
		return s_types;
	}
};

template <typename T>
struct RegisteredInTypeFactory
{
	static bool value;
};

template <typename T>
bool RegisteredInTypeFactory<T>::value{ TypeFactory::registerType(T::type()) };

#define ENUM(...)
#define CLASS(...)
#define PROPERTY(...)
#define FUNCTION(...)

#define GENERATED_BODY() \
	virtual const std::string& getTypeName() const; \
	virtual const meta_t& getTypeMeta() const ; \
	virtual const properties_t getTypeProperties() const; \
	virtual std::size_t getTypeSize() const;