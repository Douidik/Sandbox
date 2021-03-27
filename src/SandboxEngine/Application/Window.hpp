#ifndef SBX_WINDOW_HPP
#define SBX_WINDOW_HPP

#include "WindowDefinition.hpp"

class GLFWwindow;

namespace Sandbox
{

class Window
{
public:
    Window();
    ~Window();

    inline GLFWwindow *GetHandle()
    {
        return m_Handle;
    }

    inline bool IsRunning() const
    {
        return m_IsRunning;
    }

    inline const WindowDefinition &GetDefinition() const
    {
        return m_Definition;
    }

    void OnUpdate();
    void OnRender();

private:
    bool m_IsRunning;
    GLFWwindow *m_Handle;
    WindowDefinition m_Definition;
};

} // namespace Sandbox

#endif
