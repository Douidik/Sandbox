#ifndef SBX_CONTEXT_MANAGER_HPP
#define SBX_CONTEXT_MANAGER_HPP

#include "Window.hpp"

namespace Sandbox
{

class ContextManager
{
public:
    static void Init();
    static void Shut();

    ContextManager();
    ~ContextManager();

    void OnUpdate();
    void OnRender();

    inline const Window &GetWindow() const
    {
        return m_Window;
    }

private:
    Window m_Window;
};

}

#endif
