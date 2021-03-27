#include "SerializerEntry.hpp"
#include "Debug/LogManager.hpp"
#include "Misc/Tokenize.hpp"

namespace Sandbox
{

SerializerEntry::SerializerEntry(const std::string &filepath, const std::string &appName)
    : m_Filepath(filepath)
{
    m_YAMLRoot = YAML::LoadFile(m_Filepath)[appName];

    if (!m_YAMLRoot)
    {
        SBX_WARN_LOG("File \"{}\" does not provide any configuration node for the current app named \"{}\"",
                     filepath,
                     appName);
    }
}

YAML::Node FindNode(YAML::Node node, std::queue<std::string> tokens)
{
    if (tokens.empty())
        return node;

    // Dequeue the token
    std::string token = tokens.front();
    tokens.pop();

    return FindNode(node[token], tokens);
}

YAML::Node SerializerEntry::GetNode(const std::string &key)
{
    auto tokens = Tokenize(key, '.');
    return FindNode(m_YAMLRoot, tokens);
}

} // namespace Sandbox
