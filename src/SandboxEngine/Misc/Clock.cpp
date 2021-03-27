#include "Clock.hpp"

namespace Sandbox
{

Timepoint Clock::GetTime()
{
    return std::chrono::system_clock::now();
}

}
