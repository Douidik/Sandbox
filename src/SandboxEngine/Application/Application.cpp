#include "Application.hpp"

namespace Sandbox
{

Application *Application::s_Instance = nullptr;

Application *Application::Create(const std::string &name)
{
    LogManager::Init();
    ContextManager::Init();

    Serializer::Create(name);
    Serializer::GetInstance()->AddEntry("video", "video_settings.yml");

    return (s_Instance = new Application(name));
}

void Application::Destroy()
{
    delete s_Instance;

    Serializer::Destroy();
    ContextManager::Shut();
    LogManager::Shut();
}

Application::Application(const std::string &name)
    : m_Name(name)
{
}

Application::~Application()
{
}

void Application::Run()
{
    while (m_ContextManager.GetWindow().IsRunning())
    {
        Update();
        Render();
    }
}

void Application::Update()
{
    m_ContextManager.OnUpdate();
}

void Application::Render()
{
    m_ContextManager.OnRender();
}

} // namespace Sandbox
