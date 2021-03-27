#ifndef SBX_APPLICATION_HPP
#define SBX_APPLICATION_HPP

#include "Debug/LogManager.hpp"
#include "ContextManager.hpp"
#include "Serialization/Serializer.hpp"

namespace Sandbox
{

class Application
{
public:
    static Application *Create(const std::string &name);
    static void Destroy();

    inline static Application *GetInstance()
    {
        return s_Instance;
    }

public:
    Application(const std::string &name);
    ~Application();

    inline const std::string &GetName()
    {
        return m_Name;
    }

    void Run();

    void Update();
    void Render();

private:
    ContextManager m_ContextManager;

    const std::string m_Name;

    static Application *s_Instance;
};

} // namespace Sandbox

#endif
