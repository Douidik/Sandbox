#ifndef SBX_SERIALIZER_HPP
#define SBX_SERIALIZER_HPP

#include "Debug/Assertion.hpp"
#include "SerializerEntry.hpp"
#include <string>
#include <unordered_map>
#include <yaml-cpp/yaml.h>

namespace Sandbox
{

class Serializer
{
public:
    static Serializer *Create(const std::string &appName);
    static void Destroy();

    inline static Serializer *GetInstance()
    {
        SBX_ASSERT(s_Instance, "Serializer is not initialized");
        return s_Instance;
    }

    void AddEntry(const std::string &name, const std::string &filepath);
    SerializerEntry &GetEntry(const std::string &name);

    template <typename T>
    T Load(const std::string &entryName, const std::string &key)
    {
        SerializerEntry &entry = GetEntry(entryName);
        YAML::Node node = entry.GetNode(key);
        try
        {
            return node.as<T>();
        }
        catch (const YAML::BadConversion &)
        {
            SBX_ERROR("Cannot convert YAML node \"{}\" to object", key);
            return T();
        }
    }

    template <typename T>
    void Save(const std::string &entryName, const std::string &key, const T &object)
    {
        SerializerEntry &entry = GetEntry(entryName);
        YAML::Node node = entry.GetNode(key);

        try
        {
            node = object;
        }
        catch (const YAML::BadConversion &)
        {
            SBX_ERROR("Cannot convert object to YAML node \"{}\"", key);
        }
    }

private:
    Serializer(const std::string &appName);

    const std::string m_AppName;
    std::unordered_map<std::string, SerializerEntry> m_Entries;

    static Serializer *s_Instance;
};

} // namespace Sandbox

#endif
