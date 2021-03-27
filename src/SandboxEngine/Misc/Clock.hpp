#ifndef SBX_CLOCK_HPP
#define SBX_CLOCK_HPP

#include <chrono>

namespace Sandbox
{

using Timepoint = std::chrono::time_point<std::chrono::system_clock>;

class Clock
{
public:
    static Timepoint GetTime();
};

}

#endif
