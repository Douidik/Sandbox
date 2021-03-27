#include "ContextManager.hpp"
#include <GLFW/glfw3.h>
#include "Debug/Assertion.hpp"

namespace Sandbox
{

void ContextManager::Init()
{
    SBX_ASSERT(glfwInit(), "Failed to initialize GLFW");

    glfwSetErrorCallback([](int error, const char *description)
    {
        SBX_ERROR_LOG("GLFW #{}: {}", error, description);
    });
}

void ContextManager::Shut()
{
    glfwTerminate();
}

ContextManager::ContextManager()
{
    // GraphicsAPI::Init();
}

ContextManager::~ContextManager()
{
    // GraphicsAPI::Shut();
}

void ContextManager::OnUpdate()
{
    glfwPollEvents();
    m_Window.OnUpdate();
}

void ContextManager::OnRender()
{
    m_Window.OnRender();
}

}
