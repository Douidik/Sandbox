#ifndef SBX_SERIALIZER_ENTRY_HPP
#define SBX_SERIALIZER_ENTRY_HPP

#include <string>
#include <yaml-cpp/yaml.h>

namespace Sandbox
{

class SerializerEntry
{
public:
    SerializerEntry(const std::string &filepath, const std::string &appName);
    SerializerEntry() = default;
    ~SerializerEntry() = default;

    inline const std::string &GetFilepath() const
    {
        return m_Filepath;
    }

    YAML::Node GetNode(const std::string &key);

private:
    std::string m_Filepath;
    YAML::Node m_YAMLRoot;
};

}

#endif
