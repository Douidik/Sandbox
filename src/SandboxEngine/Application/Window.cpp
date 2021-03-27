#include "Window.hpp"
#include <GLFW/glfw3.h>
#include "Serialization/Serializer.hpp"

namespace Sandbox
{

Window::Window()
    : m_Definition(Serializer::GetInstance()->Load<WindowDefinition>("video", "window"))
{
    m_Handle = glfwCreateWindow(
        m_Definition.width, m_Definition.height, m_Definition.title.c_str(), nullptr, nullptr);

    glfwMakeContextCurrent(m_Handle);
}

Window::~Window()
{
    glfwDestroyWindow(m_Handle);
}

void Window::OnUpdate()
{
    m_IsRunning = glfwWindowShouldClose(m_Handle);
}

void Window::OnRender()
{
    glfwSwapBuffers(m_Handle);
}

} // namespace Sandbox
