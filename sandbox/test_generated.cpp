// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "test.h"

const char* const reflect::Enum<TestEnum>::name() { return "TestEnum"; }
const reflect::enum_values_t& reflect::Enum<TestEnum>::values()
{
    static reflect::enum_values_t s_values{
        { "A", static_cast<int>(TestEnum::A) }, 
        { "B", static_cast<int>(TestEnum::B) }, 
    };
    return s_values;
}

const char* const reflect::Enum<ApplicationMode>::name() { return "ApplicationMode"; }
const reflect::enum_values_t& reflect::Enum<ApplicationMode>::values()
{
    static reflect::enum_values_t s_values{
        { "Editor", static_cast<int>(ApplicationMode::Editor) }, 
        { "Server", static_cast<int>(ApplicationMode::Server) }, 
        { "Standalone", static_cast<int>(ApplicationMode::Standalone) }, 
    };
    return s_values;
}

const reflect::meta_t& reflect::Type<Foo>::meta()
{
    static reflect::meta_t s_meta {
        { "Category", "MyClass" },
        { "Serializable", "true" },
    };
    return s_meta;
}
const char* const reflect::Type<Foo>::name() { return "Foo"; }

const reflect::properties_t& Type<Foo>::properties()
{
    static reflect::properties_t s_properties {
        { "m_int", reflect::Property{ offsetof(Foo, m_int), reflect::meta_t {{"JsonExport", "true"} }, "m_int", reflect::PropertyType{ "int", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(int), reflect::PropertyType::Type::T_int } } },
        { "m_enum", reflect::Property{ offsetof(Foo, m_enum), reflect::meta_t { }, "m_enum", reflect::PropertyType{ "TestEnum", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(TestEnum), reflect::PropertyType::Type::T_enum } } },
        { "m_bool", reflect::Property{ offsetof(Foo, m_bool), reflect::meta_t { }, "m_bool", reflect::PropertyType{ "bool", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(bool), reflect::PropertyType::Type::T_bool } } },
        { "m_string", reflect::Property{ offsetof(Foo, m_string), reflect::meta_t { }, "m_string", reflect::PropertyType{ "std::string", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(std::string), reflect::PropertyType::Type::T_string } } },
        { "list", reflect::Property{ offsetof(Foo, list), reflect::meta_t { }, "list", reflect::PropertyType{ "std::list<int>", { 
            reflect::PropertyType{ "int", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(int), reflect::PropertyType::Type::T_int },
        }, reflect::PropertyType::DecoratorType::D_raw, sizeof(std::list<int>), reflect::PropertyType::Type::T_template } } },
        { "dictionary", reflect::Property{ offsetof(Foo, dictionary), reflect::meta_t { }, "dictionary", reflect::PropertyType{ "std::map<std::string, int>", { 
            reflect::PropertyType{ "std::string", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(std::string), reflect::PropertyType::Type::T_string },
            reflect::PropertyType{ "int", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(int), reflect::PropertyType::Type::T_int },
        }, reflect::PropertyType::DecoratorType::D_raw, sizeof(std::map<std::string, int>), reflect::PropertyType::Type::T_template } } },
        { "position", reflect::Property{ offsetof(Foo, position), reflect::meta_t { }, "position", reflect::PropertyType{ "math::vec3", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(math::vec3), reflect::PropertyType::Type::T_unknown } } },
    };
    return s_properties;
}

std::size_t reflect::Type<Foo>::size()
{
    return sizeof(Foo);
}

void reflect::Type<Foo>::from_string(const std::string& str, Foo& type)
{
    reflect::encoding::ByteBuffer buffer;
    std::transform(
        std::begin(str),
        std::end(str),
        std::back_inserter(buffer),
        [](const char c)
        {
            return std::byte(c);
        }
    );
    
    reflect::encoding::InputByteStream stream(buffer);
    std::string _name;
    stream >> _name;
    if (_name != name()) return;
    
    stream >> type.m_int;
    {
        int pack;
        stream >> pack;
        type.m_enum = static_cast<TestEnum>(type.m_enum);
    }
    stream >> type.m_bool;
    stream >> type.m_string;
    {
        std::size_t size;
        stream >> size;
        type.list.resize(size);
        for (int i = 0; i < type.list.size(); ++i)
        {
            int element;
            stream >> element;
            type.list.push_back(std::move(element));
        }
    }
    {
        std::size_t size;
        stream >> size;
        for (int i = 0; i < size; ++i)
        {
            std::string key;
            stream >> key;
            int value;
            stream >> value;
            type.dictionary.insert(std::make_pair(key, value));
        }
    }
}

std::string reflect::Type<Foo>::to_string(const Foo& type)
{
    reflect::encoding::ByteBuffer buffer;
    reflect::encoding::OutputByteStream stream(buffer);
    stream << name();
    
    stream << type.m_int;
    stream << static_cast<int>(type.m_enum);
    stream << type.m_bool;
    stream << type.m_string;
    {
        stream << type.list.size();
        for (const auto& element : type.list)
        {
        stream << element;
        }
    }
    {
        stream << type.dictionary.size();
        for (const auto& pair : type.dictionary)
        {
        stream << pair.first;
        stream << pair.second;
        }
    }
    
    return std::string(reinterpret_cast<const char*>(&stream.getBuffer()[0]), stream.getBuffer().size());
}

void reflect::Type<Foo>::from_json(const std::string& json, Foo& type)
{
    std::string src{ reflect::encoding::json::Deserializer::trim(json, reflect::encoding::json::Deserializer::space) };
    
    size_t index = 0;
    std::string key;
    while ((index = reflect::encoding::json::Deserializer::next_key(src, key)) != std::string::npos)
    {
        src = src.substr(index + 2);
        src = reflect::encoding::json::Deserializer::ltrim(src, reflect::encoding::json::Deserializer::space);
        std::string value;
        index = reflect::encoding::json::Deserializer::next_value(src, value);
        if (index != std::string::npos)
        {
            if (key == "m_int") reflect::encoding::json::Deserializer::parse(value, type.m_int);
            if (key == "m_enum")
            {
                std::string temp;
                reflect::encoding::json::Deserializer::parse(value, temp);
                stringToEnum(value, type.m_enum);
            }
            if (key == "m_bool") reflect::encoding::json::Deserializer::parse(value, type.m_bool);
            if (key == "m_string") reflect::encoding::json::Deserializer::parse(value, type.m_string);
            if (key == "list") reflect::encoding::json::Deserializer::parse(value, type.list);
            if (key == "dictionary") reflect::encoding::json::Deserializer::parse(value, type.dictionary);
            src = src.substr(index + 1);
        }
        else break;
    };
}

std::string reflect::Type<Foo>::to_json(const Foo& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "Foo" << "," << std::endl;
    stream << offset << "    " << "\"m_int\": " << reflect::encoding::json::Serializer::to_string(type.m_int) << "," << std::endl;
    stream << offset << "    " << "\"m_enum\": " << reflect::encoding::json::Serializer::to_string(enumToString(type.m_enum)) << "," << std::endl;
    stream << offset << "    " << "\"m_bool\": " << reflect::encoding::json::Serializer::to_string(type.m_bool) << "," << std::endl;
    stream << offset << "    " << "\"m_string\": " << reflect::encoding::json::Serializer::to_string(type.m_string) << "," << std::endl;
    stream << offset << "    " << "\"list\": " << reflect::encoding::json::Serializer::to_string(type.list) << "," << std::endl;
    stream << offset << "    " << "\"dictionary\": " << reflect::encoding::json::Serializer::to_string(type.dictionary) << "," << std::endl;
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& Foo::type_meta() const { return reflect::Type<Foo>::meta(); }
const char* const Foo::type_name() const { return reflect::Type<Foo>::name(); }
const reflect::properties_t& Foo::type_properties() const { return reflect::Type<Foo>::properties(); }
Foo::operator std::string() const { return reflect::Type<Foo>::to_string(*this); }
void Foo::from_string(const std::string& str) { reflect::Type<Foo>::from_string(str, *this); }
void Foo::from_json(const std::string& json) { reflect::Type<Foo>::from_json(json, *this); }
std::string Foo::to_json(const std::string& offset) const { return reflect::Type<Foo>::to_json(*this, offset); }

const reflect::meta_t& reflect::Type<Poo>::meta()
{
    static reflect::meta_t s_meta {
    };
    return s_meta;
}
const char* const reflect::Type<Poo>::name() { return "Poo"; }

const reflect::properties_t& Type<Poo>::properties()
{
    static reflect::properties_t s_properties {
        // Parent class Foo properties
        { "m_int", reflect::Property{ offsetof(Poo, m_int), reflect::meta_t {{"JsonExport", "true"} }, "m_int", reflect::PropertyType{ "int", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(int), reflect::PropertyType::Type::T_int } } },
        { "m_enum", reflect::Property{ offsetof(Poo, m_enum), reflect::meta_t { }, "m_enum", reflect::PropertyType{ "TestEnum", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(TestEnum), reflect::PropertyType::Type::T_enum } } },
        { "m_bool", reflect::Property{ offsetof(Poo, m_bool), reflect::meta_t { }, "m_bool", reflect::PropertyType{ "bool", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(bool), reflect::PropertyType::Type::T_bool } } },
        { "m_string", reflect::Property{ offsetof(Poo, m_string), reflect::meta_t { }, "m_string", reflect::PropertyType{ "std::string", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(std::string), reflect::PropertyType::Type::T_string } } },
        { "list", reflect::Property{ offsetof(Poo, list), reflect::meta_t { }, "list", reflect::PropertyType{ "std::list<int>", { 
            reflect::PropertyType{ "int", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(int), reflect::PropertyType::Type::T_int },
        }, reflect::PropertyType::DecoratorType::D_raw, sizeof(std::list<int>), reflect::PropertyType::Type::T_template } } },
        { "dictionary", reflect::Property{ offsetof(Poo, dictionary), reflect::meta_t { }, "dictionary", reflect::PropertyType{ "std::map<std::string, int>", { 
            reflect::PropertyType{ "std::string", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(std::string), reflect::PropertyType::Type::T_string },
            reflect::PropertyType{ "int", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(int), reflect::PropertyType::Type::T_int },
        }, reflect::PropertyType::DecoratorType::D_raw, sizeof(std::map<std::string, int>), reflect::PropertyType::Type::T_template } } },
        { "position", reflect::Property{ offsetof(Poo, position), reflect::meta_t { }, "position", reflect::PropertyType{ "math::vec3", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(math::vec3), reflect::PropertyType::Type::T_unknown } } },
        // Properties
        { "c", reflect::Property{ offsetof(Poo, c), reflect::meta_t { }, "c", reflect::PropertyType{ "int", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(int), reflect::PropertyType::Type::T_int } } },
        { "tuple", reflect::Property{ offsetof(Poo, tuple), reflect::meta_t { }, "tuple", reflect::PropertyType{ "std::tuple<int, float, bool, double>", { 
            reflect::PropertyType{ "int", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(int), reflect::PropertyType::Type::T_int },
            reflect::PropertyType{ "float", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(float), reflect::PropertyType::Type::T_float },
            reflect::PropertyType{ "bool", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(bool), reflect::PropertyType::Type::T_bool },
            reflect::PropertyType{ "double", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(double), reflect::PropertyType::Type::T_double },
        }, reflect::PropertyType::DecoratorType::D_raw, sizeof(std::tuple<int, float, bool, double>), reflect::PropertyType::Type::T_template } } },
        { "power_dictionary", reflect::Property{ offsetof(Poo, power_dictionary), reflect::meta_t { }, "power_dictionary", reflect::PropertyType{ "std::map<std::string, std::vector<int>>", { 
            reflect::PropertyType{ "std::string", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(std::string), reflect::PropertyType::Type::T_string },
            reflect::PropertyType{ "std::vector<int>", { 
                reflect::PropertyType{ "int", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(int), reflect::PropertyType::Type::T_int },
            }, reflect::PropertyType::DecoratorType::D_raw, sizeof(std::vector<int>), reflect::PropertyType::Type::T_template },
        }, reflect::PropertyType::DecoratorType::D_raw, sizeof(std::map<std::string, std::vector<int>>), reflect::PropertyType::Type::T_template } } },
        { "shared_foos", reflect::Property{ offsetof(Poo, shared_foos), reflect::meta_t { }, "shared_foos", reflect::PropertyType{ "std::vector<std::shared_ptr<Foo>>", { 
            reflect::PropertyType{ "std::shared_ptr<Foo>", { 
                reflect::PropertyType{ "Foo", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(Foo), reflect::PropertyType::Type::T_type },
            }, reflect::PropertyType::DecoratorType::D_raw, sizeof(std::shared_ptr<Foo>), reflect::PropertyType::Type::T_template },
        }, reflect::PropertyType::DecoratorType::D_raw, sizeof(std::vector<std::shared_ptr<Foo>>), reflect::PropertyType::Type::T_template } } },
        { "unique_foos", reflect::Property{ offsetof(Poo, unique_foos), reflect::meta_t { }, "unique_foos", reflect::PropertyType{ "std::vector<std::unique_ptr<Foo>>", { 
            reflect::PropertyType{ "std::unique_ptr<Foo>", { 
                reflect::PropertyType{ "Foo", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(Foo), reflect::PropertyType::Type::T_type },
            }, reflect::PropertyType::DecoratorType::D_raw, sizeof(std::unique_ptr<Foo>), reflect::PropertyType::Type::T_template },
        }, reflect::PropertyType::DecoratorType::D_raw, sizeof(std::vector<std::unique_ptr<Foo>>), reflect::PropertyType::Type::T_template } } },
        { "type", reflect::Property{ offsetof(Poo, type), reflect::meta_t { }, "type", reflect::PropertyType{ "Foo", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(Foo), reflect::PropertyType::Type::T_type } } },
        { "s_type", reflect::Property{ offsetof(Poo, s_type), reflect::meta_t { }, "s_type", reflect::PropertyType{ "std::shared_ptr<Foo>", { 
            reflect::PropertyType{ "Foo", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(Foo), reflect::PropertyType::Type::T_type },
        }, reflect::PropertyType::DecoratorType::D_raw, sizeof(std::shared_ptr<Foo>), reflect::PropertyType::Type::T_template } } },
        { "u_type", reflect::Property{ offsetof(Poo, u_type), reflect::meta_t { }, "u_type", reflect::PropertyType{ "std::unique_ptr<Foo>", { 
            reflect::PropertyType{ "Foo", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(Foo), reflect::PropertyType::Type::T_type },
        }, reflect::PropertyType::DecoratorType::D_raw, sizeof(std::unique_ptr<Foo>), reflect::PropertyType::Type::T_template } } },
    };
    return s_properties;
}

std::size_t reflect::Type<Poo>::size()
{
    return sizeof(Poo);
}

void reflect::Type<Poo>::from_string(const std::string& str, Poo& type)
{
    reflect::encoding::ByteBuffer buffer;
    std::transform(
        std::begin(str),
        std::end(str),
        std::back_inserter(buffer),
        [](const char c)
        {
            return std::byte(c);
        }
    );
    
    reflect::encoding::InputByteStream stream(buffer);
    std::string _name;
    stream >> _name;
    if (_name != name()) return;
    
    // Parent class Foo properties
    stream >> type.m_int;
    {
        int pack;
        stream >> pack;
        type.m_enum = static_cast<TestEnum>(type.m_enum);
    }
    stream >> type.m_bool;
    stream >> type.m_string;
    {
        std::size_t size;
        stream >> size;
        type.list.resize(size);
        for (int i = 0; i < type.list.size(); ++i)
        {
            int element;
            stream >> element;
            type.list.push_back(std::move(element));
        }
    }
    {
        std::size_t size;
        stream >> size;
        for (int i = 0; i < size; ++i)
        {
            std::string key;
            stream >> key;
            int value;
            stream >> value;
            type.dictionary.insert(std::make_pair(key, value));
        }
    }
    // Properties
    stream >> type.c;
    {
        std::size_t size;
        stream >> size;
        type.shared_foos.resize(size);
        for (int i = 0; i < type.shared_foos.size(); ++i)
        {
            std::shared_ptr<Foo> element;
            element = std::make_shared<Foo>();
            {
                std::string pack;
                stream >> pack;
                element->from_string(pack);
            }
            type.shared_foos.push_back(std::move(element));
        }
    }
    {
        std::size_t size;
        stream >> size;
        type.unique_foos.resize(size);
        for (int i = 0; i < type.unique_foos.size(); ++i)
        {
            std::unique_ptr<Foo> element;
            element = std::make_unique<Foo>();
            {
                std::string pack;
                stream >> pack;
                element->from_string(pack);
            }
            type.unique_foos.push_back(std::move(element));
        }
    }
    {
        std::string pack;
        stream >> pack;
        type.type.from_string(pack);
    }
    type.s_type = std::make_shared<Foo>();
    {
        std::string pack;
        stream >> pack;
        type.s_type->from_string(pack);
    }
    type.u_type = std::make_unique<Foo>();
    {
        std::string pack;
        stream >> pack;
        type.u_type->from_string(pack);
    }
}

std::string reflect::Type<Poo>::to_string(const Poo& type)
{
    reflect::encoding::ByteBuffer buffer;
    reflect::encoding::OutputByteStream stream(buffer);
    stream << name();
    
    // Parent class Foo properties
    stream << type.m_int;
    stream << static_cast<int>(type.m_enum);
    stream << type.m_bool;
    stream << type.m_string;
    {
        stream << type.list.size();
        for (const auto& element : type.list)
        {
        stream << element;
        }
    }
    {
        stream << type.dictionary.size();
        for (const auto& pair : type.dictionary)
        {
        stream << pair.first;
        stream << pair.second;
        }
    }
    // Properties
    stream << type.c;
    {
        stream << type.shared_foos.size();
        for (const auto& element : type.shared_foos)
        {
        if(element) stream << static_cast<std::string>(*element);
        }
    }
    {
        stream << type.unique_foos.size();
        for (const auto& element : type.unique_foos)
        {
        if(element) stream << static_cast<std::string>(*element);
        }
    }
    stream << static_cast<std::string>(type.type);
    if(type.s_type) stream << static_cast<std::string>(*type.s_type);
    if(type.u_type) stream << static_cast<std::string>(*type.u_type);
    
    return std::string(reinterpret_cast<const char*>(&stream.getBuffer()[0]), stream.getBuffer().size());
}

void reflect::Type<Poo>::from_json(const std::string& json, Poo& type)
{
    std::string src{ reflect::encoding::json::Deserializer::trim(json, reflect::encoding::json::Deserializer::space) };
    
    size_t index = 0;
    std::string key;
    while ((index = reflect::encoding::json::Deserializer::next_key(src, key)) != std::string::npos)
    {
        src = src.substr(index + 2);
        src = reflect::encoding::json::Deserializer::ltrim(src, reflect::encoding::json::Deserializer::space);
        std::string value;
        index = reflect::encoding::json::Deserializer::next_value(src, value);
        if (index != std::string::npos)
        {
            // Parent class Foo properties
            if (key == "m_int") reflect::encoding::json::Deserializer::parse(value, type.m_int);
            if (key == "m_enum")
            {
                std::string temp;
                reflect::encoding::json::Deserializer::parse(value, temp);
                stringToEnum(value, type.m_enum);
            }
            if (key == "m_bool") reflect::encoding::json::Deserializer::parse(value, type.m_bool);
            if (key == "m_string") reflect::encoding::json::Deserializer::parse(value, type.m_string);
            if (key == "list") reflect::encoding::json::Deserializer::parse(value, type.list);
            if (key == "dictionary") reflect::encoding::json::Deserializer::parse(value, type.dictionary);
            // Properties
            if (key == "c") reflect::encoding::json::Deserializer::parse(value, type.c);
            if (key == "shared_foos") reflect::encoding::json::Deserializer::parse(value, type.shared_foos);
            if (key == "unique_foos") reflect::encoding::json::Deserializer::parse(value, type.unique_foos);
            if (key == "type") type.type.from_json(value);
            if (key == "s_type") reflect::encoding::json::Deserializer::parse(value, type.s_type);
            if (key == "u_type") reflect::encoding::json::Deserializer::parse(value, type.u_type);
            src = src.substr(index + 1);
        }
        else break;
    };
}

std::string reflect::Type<Poo>::to_json(const Poo& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "Poo" << "," << std::endl;
    // Parent class Foo properties
    stream << offset << "    " << "\"m_int\": " << reflect::encoding::json::Serializer::to_string(type.m_int) << "," << std::endl;
    stream << offset << "    " << "\"m_enum\": " << reflect::encoding::json::Serializer::to_string(enumToString(type.m_enum)) << "," << std::endl;
    stream << offset << "    " << "\"m_bool\": " << reflect::encoding::json::Serializer::to_string(type.m_bool) << "," << std::endl;
    stream << offset << "    " << "\"m_string\": " << reflect::encoding::json::Serializer::to_string(type.m_string) << "," << std::endl;
    stream << offset << "    " << "\"list\": " << reflect::encoding::json::Serializer::to_string(type.list) << "," << std::endl;
    stream << offset << "    " << "\"dictionary\": " << reflect::encoding::json::Serializer::to_string(type.dictionary) << "," << std::endl;
    // Properties
    stream << offset << "    " << "\"c\": " << reflect::encoding::json::Serializer::to_string(type.c) << "," << std::endl;
    stream << offset << "    " << "\"shared_foos\": " << reflect::encoding::json::Serializer::to_string(type.shared_foos) << "," << std::endl;
    stream << offset << "    " << "\"unique_foos\": " << reflect::encoding::json::Serializer::to_string(type.unique_foos) << "," << std::endl;
    stream << offset << "    " << "\"type\": " << type.type.to_json(offset + "    ") << "," << std::endl;
    stream << offset << "    " << "\"s_type\": " << reflect::encoding::json::Serializer::to_string(type.s_type) << "," << std::endl;
    stream << offset << "    " << "\"u_type\": " << reflect::encoding::json::Serializer::to_string(type.u_type) << "," << std::endl;
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& Poo::type_meta() const { return reflect::Type<Poo>::meta(); }
const char* const Poo::type_name() const { return reflect::Type<Poo>::name(); }
const reflect::properties_t& Poo::type_properties() const { return reflect::Type<Poo>::properties(); }
Poo::operator std::string() const { return reflect::Type<Poo>::to_string(*this); }
void Poo::from_string(const std::string& str) { reflect::Type<Poo>::from_string(str, *this); }
void Poo::from_json(const std::string& json) { reflect::Type<Poo>::from_json(json, *this); }
std::string Poo::to_json(const std::string& offset) const { return reflect::Type<Poo>::to_json(*this, offset); }

