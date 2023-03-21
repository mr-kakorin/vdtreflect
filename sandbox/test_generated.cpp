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
        { "m_int", reflect::Property{ offsetof(Foo, m_int), reflect::meta_t {{"JsonExport", "true"} }, "m_int", reflect::NativeType{ "int", {  }, reflect::NativeType::DecoratorType::D_raw, sizeof(int), reflect::NativeType::Type::T_int } } },
        { "m_enum", reflect::Property{ offsetof(Foo, m_enum), reflect::meta_t { }, "m_enum", reflect::NativeType{ "TestEnum", {  }, reflect::NativeType::DecoratorType::D_raw, sizeof(TestEnum), reflect::NativeType::Type::T_enum } } },
        { "m_bool", reflect::Property{ offsetof(Foo, m_bool), reflect::meta_t { }, "m_bool", reflect::NativeType{ "bool", {  }, reflect::NativeType::DecoratorType::D_raw, sizeof(bool), reflect::NativeType::Type::T_bool } } },
        { "m_string", reflect::Property{ offsetof(Foo, m_string), reflect::meta_t { }, "m_string", reflect::NativeType{ "std::string", {  }, reflect::NativeType::DecoratorType::D_raw, sizeof(std::string), reflect::NativeType::Type::T_string } } },
        { "list", reflect::Property{ offsetof(Foo, list), reflect::meta_t { }, "list", reflect::NativeType{ "std::list<int>", { 
            reflect::NativeType{ "int", {  }, reflect::NativeType::DecoratorType::D_raw, sizeof(int), reflect::NativeType::Type::T_int },
        }, reflect::NativeType::DecoratorType::D_raw, sizeof(std::list<int>), reflect::NativeType::Type::T_template } } },
        { "dictionary", reflect::Property{ offsetof(Foo, dictionary), reflect::meta_t { }, "dictionary", reflect::NativeType{ "std::map<std::string, int>", { 
            reflect::NativeType{ "std::string", {  }, reflect::NativeType::DecoratorType::D_raw, sizeof(std::string), reflect::NativeType::Type::T_string },
            reflect::NativeType{ "int", {  }, reflect::NativeType::DecoratorType::D_raw, sizeof(int), reflect::NativeType::Type::T_int },
        }, reflect::NativeType::DecoratorType::D_raw, sizeof(std::map<std::string, int>), reflect::NativeType::Type::T_template } } },
    };
    return s_properties;
}

const reflect::meta_t& Foo::type_meta() const { return reflect::Type<Foo>::meta(); }
const char* const Foo::type_name() const { return reflect::Type<Foo>::name(); }
const reflect::properties_t& Foo::type_properties() const { return reflect::Type<Foo>::properties(); }

Foo::operator std::string() const
{
    reflect::encoding::ByteBuffer buffer;
    reflect::encoding::OutputByteStream stream(buffer);
    stream << type_name();
    
    stream << m_int;
    stream << static_cast<int>(m_enum);
    stream << m_bool;
    stream << m_string;
    {
        stream << list.size();
        for (const auto& element : list)
        {
        stream << element;
        }
    }
    {
        stream << dictionary.size();
        for (const auto& pair : dictionary)
        {
        stream << pair.first;
        stream << pair.second;
        }
    }
    
    return std::string(reinterpret_cast<const char*>(&stream.getBuffer()[0]), stream.getBuffer().size());
}

void Foo::from_string(const std::string& str)
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
    if (_name != type_name()) return;
    
    stream >> m_int;
    {
        int pack;
        stream >> pack;
        m_enum = static_cast<TestEnum>(m_enum);
    }
    stream >> m_bool;
    stream >> m_string;
    {
        std::size_t size;
        stream >> size;
        list.resize(size);
        for (int i = 0; i < list.size(); ++i)
        {
            int element;
            stream >> element;
            list.push_back(std::move(element));
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
            dictionary.insert(std::make_pair(key, value));
        }
    }
}

void Foo::from_json(const std::string& json)
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
            if (key == "m_int") reflect::encoding::json::Deserializer::parse(value, m_int);
            if (key == "m_enum")
            {
                std::string temp;
                reflect::encoding::json::Deserializer::parse(value, temp);
                stringToEnum(value, m_enum);
            }
            if (key == "m_bool") reflect::encoding::json::Deserializer::parse(value, m_bool);
            if (key == "m_string") reflect::encoding::json::Deserializer::parse(value, m_string);
            if (key == "list") reflect::encoding::json::Deserializer::parse(value, list);
            if (key == "dictionary") reflect::encoding::json::Deserializer::parse(value, dictionary);
            src = src.substr(index + 1);
        }
        else break;
    };
}

std::string Foo::to_json(const std::string& offset) const
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "Foo" << "," << std::endl;
    stream << offset << "    " << "\"m_int\": " << reflect::encoding::json::Serializer::to_string(m_int) << "," << std::endl;
    stream << offset << "    " << "\"m_enum\": " << reflect::encoding::json::Serializer::to_string(enumToString(m_enum)) << "," << std::endl;
    stream << offset << "    " << "\"m_bool\": " << reflect::encoding::json::Serializer::to_string(m_bool) << "," << std::endl;
    stream << offset << "    " << "\"m_string\": " << reflect::encoding::json::Serializer::to_string(m_string) << "," << std::endl;
    stream << offset << "    " << "\"list\": " << reflect::encoding::json::Serializer::to_string(list) << "," << std::endl;
    stream << offset << "    " << "\"dictionary\": " << reflect::encoding::json::Serializer::to_string(dictionary) << "," << std::endl;
    stream << offset << "}";
    return stream.str();
}

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
        { "m_int", reflect::Property{ offsetof(Poo, m_int), reflect::meta_t {{"JsonExport", "true"} }, "m_int", reflect::NativeType{ "int", {  }, reflect::NativeType::DecoratorType::D_raw, sizeof(int), reflect::NativeType::Type::T_int } } },
        { "m_enum", reflect::Property{ offsetof(Poo, m_enum), reflect::meta_t { }, "m_enum", reflect::NativeType{ "TestEnum", {  }, reflect::NativeType::DecoratorType::D_raw, sizeof(TestEnum), reflect::NativeType::Type::T_enum } } },
        { "m_bool", reflect::Property{ offsetof(Poo, m_bool), reflect::meta_t { }, "m_bool", reflect::NativeType{ "bool", {  }, reflect::NativeType::DecoratorType::D_raw, sizeof(bool), reflect::NativeType::Type::T_bool } } },
        { "m_string", reflect::Property{ offsetof(Poo, m_string), reflect::meta_t { }, "m_string", reflect::NativeType{ "std::string", {  }, reflect::NativeType::DecoratorType::D_raw, sizeof(std::string), reflect::NativeType::Type::T_string } } },
        { "list", reflect::Property{ offsetof(Poo, list), reflect::meta_t { }, "list", reflect::NativeType{ "std::list<int>", { 
            reflect::NativeType{ "int", {  }, reflect::NativeType::DecoratorType::D_raw, sizeof(int), reflect::NativeType::Type::T_int },
        }, reflect::NativeType::DecoratorType::D_raw, sizeof(std::list<int>), reflect::NativeType::Type::T_template } } },
        { "dictionary", reflect::Property{ offsetof(Poo, dictionary), reflect::meta_t { }, "dictionary", reflect::NativeType{ "std::map<std::string, int>", { 
            reflect::NativeType{ "std::string", {  }, reflect::NativeType::DecoratorType::D_raw, sizeof(std::string), reflect::NativeType::Type::T_string },
            reflect::NativeType{ "int", {  }, reflect::NativeType::DecoratorType::D_raw, sizeof(int), reflect::NativeType::Type::T_int },
        }, reflect::NativeType::DecoratorType::D_raw, sizeof(std::map<std::string, int>), reflect::NativeType::Type::T_template } } },
        // Properties
        { "c", reflect::Property{ offsetof(Poo, c), reflect::meta_t { }, "c", reflect::NativeType{ "int", {  }, reflect::NativeType::DecoratorType::D_raw, sizeof(int), reflect::NativeType::Type::T_int } } },
        { "tuple", reflect::Property{ offsetof(Poo, tuple), reflect::meta_t { }, "tuple", reflect::NativeType{ "std::tuple<int, float, bool, double>", { 
            reflect::NativeType{ "int", {  }, reflect::NativeType::DecoratorType::D_raw, sizeof(int), reflect::NativeType::Type::T_int },
            reflect::NativeType{ "float", {  }, reflect::NativeType::DecoratorType::D_raw, sizeof(float), reflect::NativeType::Type::T_float },
            reflect::NativeType{ "bool", {  }, reflect::NativeType::DecoratorType::D_raw, sizeof(bool), reflect::NativeType::Type::T_bool },
            reflect::NativeType{ "double", {  }, reflect::NativeType::DecoratorType::D_raw, sizeof(double), reflect::NativeType::Type::T_double },
        }, reflect::NativeType::DecoratorType::D_raw, sizeof(std::tuple<int, float, bool, double>), reflect::NativeType::Type::T_template } } },
        { "power_dictionary", reflect::Property{ offsetof(Poo, power_dictionary), reflect::meta_t { }, "power_dictionary", reflect::NativeType{ "std::map<std::string, std::vector<int>>", { 
            reflect::NativeType{ "std::string", {  }, reflect::NativeType::DecoratorType::D_raw, sizeof(std::string), reflect::NativeType::Type::T_string },
            reflect::NativeType{ "std::vector<int>", { 
                reflect::NativeType{ "int", {  }, reflect::NativeType::DecoratorType::D_raw, sizeof(int), reflect::NativeType::Type::T_int },
            }, reflect::NativeType::DecoratorType::D_raw, sizeof(std::vector<int>), reflect::NativeType::Type::T_template },
        }, reflect::NativeType::DecoratorType::D_raw, sizeof(std::map<std::string, std::vector<int>>), reflect::NativeType::Type::T_template } } },
        { "shared_foos", reflect::Property{ offsetof(Poo, shared_foos), reflect::meta_t { }, "shared_foos", reflect::NativeType{ "std::vector<std::shared_ptr<Foo>>", { 
            reflect::NativeType{ "std::shared_ptr<Foo>", { 
                reflect::NativeType{ "Foo", {  }, reflect::NativeType::DecoratorType::D_raw, sizeof(Foo), reflect::NativeType::Type::T_type },
            }, reflect::NativeType::DecoratorType::D_raw, sizeof(std::shared_ptr<Foo>), reflect::NativeType::Type::T_template },
        }, reflect::NativeType::DecoratorType::D_raw, sizeof(std::vector<std::shared_ptr<Foo>>), reflect::NativeType::Type::T_template } } },
        { "unique_foos", reflect::Property{ offsetof(Poo, unique_foos), reflect::meta_t { }, "unique_foos", reflect::NativeType{ "std::vector<std::unique_ptr<Foo>>", { 
            reflect::NativeType{ "std::unique_ptr<Foo>", { 
                reflect::NativeType{ "Foo", {  }, reflect::NativeType::DecoratorType::D_raw, sizeof(Foo), reflect::NativeType::Type::T_type },
            }, reflect::NativeType::DecoratorType::D_raw, sizeof(std::unique_ptr<Foo>), reflect::NativeType::Type::T_template },
        }, reflect::NativeType::DecoratorType::D_raw, sizeof(std::vector<std::unique_ptr<Foo>>), reflect::NativeType::Type::T_template } } },
        { "type", reflect::Property{ offsetof(Poo, type), reflect::meta_t { }, "type", reflect::NativeType{ "Foo", {  }, reflect::NativeType::DecoratorType::D_raw, sizeof(Foo), reflect::NativeType::Type::T_type } } },
        { "s_type", reflect::Property{ offsetof(Poo, s_type), reflect::meta_t { }, "s_type", reflect::NativeType{ "std::shared_ptr<Foo>", { 
            reflect::NativeType{ "Foo", {  }, reflect::NativeType::DecoratorType::D_raw, sizeof(Foo), reflect::NativeType::Type::T_type },
        }, reflect::NativeType::DecoratorType::D_raw, sizeof(std::shared_ptr<Foo>), reflect::NativeType::Type::T_template } } },
        { "u_type", reflect::Property{ offsetof(Poo, u_type), reflect::meta_t { }, "u_type", reflect::NativeType{ "std::unique_ptr<Foo>", { 
            reflect::NativeType{ "Foo", {  }, reflect::NativeType::DecoratorType::D_raw, sizeof(Foo), reflect::NativeType::Type::T_type },
        }, reflect::NativeType::DecoratorType::D_raw, sizeof(std::unique_ptr<Foo>), reflect::NativeType::Type::T_template } } },
    };
    return s_properties;
}

const reflect::meta_t& Poo::type_meta() const { return reflect::Type<Poo>::meta(); }
const char* const Poo::type_name() const { return reflect::Type<Poo>::name(); }
const reflect::properties_t& Poo::type_properties() const { return reflect::Type<Poo>::properties(); }

Poo::operator std::string() const
{
    reflect::encoding::ByteBuffer buffer;
    reflect::encoding::OutputByteStream stream(buffer);
    stream << type_name();
    
    // Parent class Foo properties
    stream << m_int;
    stream << static_cast<int>(m_enum);
    stream << m_bool;
    stream << m_string;
    {
        stream << list.size();
        for (const auto& element : list)
        {
        stream << element;
        }
    }
    {
        stream << dictionary.size();
        for (const auto& pair : dictionary)
        {
        stream << pair.first;
        stream << pair.second;
        }
    }
    // Properties
    stream << c;
    {
        stream << shared_foos.size();
        for (const auto& element : shared_foos)
        {
        if(element) stream << static_cast<std::string>(*element);
        }
    }
    {
        stream << unique_foos.size();
        for (const auto& element : unique_foos)
        {
        if(element) stream << static_cast<std::string>(*element);
        }
    }
    stream << static_cast<std::string>(type);
    if(s_type) stream << static_cast<std::string>(*s_type);
    if(u_type) stream << static_cast<std::string>(*u_type);
    
    return std::string(reinterpret_cast<const char*>(&stream.getBuffer()[0]), stream.getBuffer().size());
}

void Poo::from_string(const std::string& str)
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
    if (_name != type_name()) return;
    
    // Parent class Foo properties
    stream >> m_int;
    {
        int pack;
        stream >> pack;
        m_enum = static_cast<TestEnum>(m_enum);
    }
    stream >> m_bool;
    stream >> m_string;
    {
        std::size_t size;
        stream >> size;
        list.resize(size);
        for (int i = 0; i < list.size(); ++i)
        {
            int element;
            stream >> element;
            list.push_back(std::move(element));
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
            dictionary.insert(std::make_pair(key, value));
        }
    }
    // Properties
    stream >> c;
    {
        std::size_t size;
        stream >> size;
        shared_foos.resize(size);
        for (int i = 0; i < shared_foos.size(); ++i)
        {
            std::shared_ptr<Foo> element;
            element = std::make_shared<Foo>();
            {
                std::string pack;
                stream >> pack;
                element->from_string(pack);
            }
            shared_foos.push_back(std::move(element));
        }
    }
    {
        std::size_t size;
        stream >> size;
        unique_foos.resize(size);
        for (int i = 0; i < unique_foos.size(); ++i)
        {
            std::unique_ptr<Foo> element;
            element = std::make_unique<Foo>();
            {
                std::string pack;
                stream >> pack;
                element->from_string(pack);
            }
            unique_foos.push_back(std::move(element));
        }
    }
    {
        std::string pack;
        stream >> pack;
        type.from_string(pack);
    }
    s_type = std::make_shared<Foo>();
    {
        std::string pack;
        stream >> pack;
        s_type->from_string(pack);
    }
    u_type = std::make_unique<Foo>();
    {
        std::string pack;
        stream >> pack;
        u_type->from_string(pack);
    }
}

void Poo::from_json(const std::string& json)
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
            if (key == "m_int") reflect::encoding::json::Deserializer::parse(value, m_int);
            if (key == "m_enum")
            {
                std::string temp;
                reflect::encoding::json::Deserializer::parse(value, temp);
                stringToEnum(value, m_enum);
            }
            if (key == "m_bool") reflect::encoding::json::Deserializer::parse(value, m_bool);
            if (key == "m_string") reflect::encoding::json::Deserializer::parse(value, m_string);
            if (key == "list") reflect::encoding::json::Deserializer::parse(value, list);
            if (key == "dictionary") reflect::encoding::json::Deserializer::parse(value, dictionary);
            // Properties
            if (key == "c") reflect::encoding::json::Deserializer::parse(value, c);
            if (key == "shared_foos") reflect::encoding::json::Deserializer::parse(value, shared_foos);
            if (key == "unique_foos") reflect::encoding::json::Deserializer::parse(value, unique_foos);
            if (key == "type") type.from_json(value);
            if (key == "s_type") reflect::encoding::json::Deserializer::parse(value, s_type);
            if (key == "u_type") reflect::encoding::json::Deserializer::parse(value, u_type);
            src = src.substr(index + 1);
        }
        else break;
    };
}

std::string Poo::to_json(const std::string& offset) const
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "Poo" << "," << std::endl;
    // Parent class Foo properties
    stream << offset << "    " << "\"m_int\": " << reflect::encoding::json::Serializer::to_string(m_int) << "," << std::endl;
    stream << offset << "    " << "\"m_enum\": " << reflect::encoding::json::Serializer::to_string(enumToString(m_enum)) << "," << std::endl;
    stream << offset << "    " << "\"m_bool\": " << reflect::encoding::json::Serializer::to_string(m_bool) << "," << std::endl;
    stream << offset << "    " << "\"m_string\": " << reflect::encoding::json::Serializer::to_string(m_string) << "," << std::endl;
    stream << offset << "    " << "\"list\": " << reflect::encoding::json::Serializer::to_string(list) << "," << std::endl;
    stream << offset << "    " << "\"dictionary\": " << reflect::encoding::json::Serializer::to_string(dictionary) << "," << std::endl;
    // Properties
    stream << offset << "    " << "\"c\": " << reflect::encoding::json::Serializer::to_string(c) << "," << std::endl;
    stream << offset << "    " << "\"shared_foos\": " << reflect::encoding::json::Serializer::to_string(shared_foos) << "," << std::endl;
    stream << offset << "    " << "\"unique_foos\": " << reflect::encoding::json::Serializer::to_string(unique_foos) << "," << std::endl;
    stream << offset << "    " << "\"type\": " << type.to_json(offset + "    ") << "," << std::endl;
    stream << offset << "    " << "\"s_type\": " << reflect::encoding::json::Serializer::to_string(s_type) << "," << std::endl;
    stream << offset << "    " << "\"u_type\": " << reflect::encoding::json::Serializer::to_string(u_type) << "," << std::endl;
    stream << offset << "}";
    return stream.str();
}

