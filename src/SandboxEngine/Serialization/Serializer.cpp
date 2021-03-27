#include "Serializer.hpp"
#include "Debug/Assertion.hpp"

namespace Sandbox
{

Serializer *Serializer::s_Instance = nullptr;

Serializer *Serializer::Create(const std::string &appName)
{
    return (s_Instance = new Serializer(appName));
}

void Serializer::Destroy()
{
    delete s_Instance;
}

Serializer::Serializer(const std::string &appName)
    : m_AppName(appName)
{ }

void Serializer::AddEntry(const std::string &name, const std::string &filepath)
{
    m_Entries[name] = SerializerEntry(filepath, m_AppName);
}

SerializerEntry &Serializer::GetEntry(const std::string &name)
{
    auto entryIt = m_Entries.find(name);
    SBX_ASSERT(entryIt != m_Entries.end(), "Undefined serialization entry named \"{}\"", name);
    return entryIt->second;
}

}
