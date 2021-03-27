#ifndef SBX_WINDOW_DEFINITION_HPP
#define SBX_WINDOW_DEFINITION_HPP

#include <string>
#include <yaml-cpp/yaml.h>

namespace Sandbox
{

enum class WindowFlag : int
{
    None = 0,
    Resizable = 1 << 0,
    Visible = 1 << 1,
    Decorated = 1 << 2,
    Iconify = 1 << 3,
    Focused = 1 << 4,
    Maximized = 1 << 5
};

struct WindowDefinition
{
    std::string title;
    int flags = (int)WindowFlag::None;
    int width, height, x, y;
};

static bool operator==(const WindowDefinition &lhs, const WindowDefinition &rhs)
{
    // We only want to check flags that are serialized
    auto CreateCheckedFlags = [](int flags) -> int {
        int checkedFlags = (int)WindowFlag::None;
        checkedFlags |= flags & (int)WindowFlag::Resizable;
        checkedFlags |= flags & (int)WindowFlag::Visible;
        checkedFlags |= flags & (int)WindowFlag::Decorated;

        return checkedFlags;
    };

    if (lhs.title != rhs.title)
        return false;

    if (CreateCheckedFlags(lhs.flags) != CreateCheckedFlags(rhs.flags))
        return false;

    if (lhs.width != rhs.width && lhs.height != rhs.height)
        return false;

    return true;
}

} // namespace Sandbox

namespace YAML
{

template <>
struct convert<Sandbox::WindowDefinition>
{

    static Node encode(const Sandbox::WindowDefinition &windowDef)
    {
        using namespace Sandbox;

        Node node;
        node["title"] = windowDef.title;
        node["resizable"] = (bool)(windowDef.flags & (int)WindowFlag::Resizable);
        node["visible"] = (bool)(windowDef.flags & (int)WindowFlag::Visible);
        node["decorated"] = (bool)(windowDef.flags & (int)WindowFlag::Decorated);
        // The window size is voluntarily not encoded but just decoded
        return node;
    }

    static bool decode(const Node &node, Sandbox::WindowDefinition &windowDef)
    {
        using namespace Sandbox;

        windowDef.title = node["title"].as<std::string>();
        windowDef.width = node["width"].as<int>();
        windowDef.height = node["height"].as<int>();

        int resizable = node["resizable"].as<int>();
        int visible = node["visible"].as<int>();
        int decorated = node["decorated"].as<int>();
        windowDef.flags = (int)WindowFlag::None | resizable | visible | decorated;

        return true;
    }
};

} // namespace YAML

#endif
