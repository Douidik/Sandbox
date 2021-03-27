#include "LogManager.hpp"
#include <iomanip>
#include <sstream>
#include "Debug/Assertion.hpp"

namespace Sandbox
{

LogManager *LogManager::s_Instance = nullptr;

LogManager *LogManager::GetInstance()
{
    //SBX_ASSERT(s_Instance != nullptr, "LogManager is not yet initialized");
    return s_Instance;
}

LogManager::LogManager()
{
    std::string time = FormatTime(Clock::GetTime(), s_LogFileTimePattern);
    std::string filename = "logs/Sandbox_" + time + ".log";

    m_LogFile = std::ofstream(filename);
}

void LogManager::PrintBuffer(const fmt::text_style &style, const fmt::memory_buffer &buffer)
{
    fmt::print(style, buffer.data());
}

void LogManager::WriteBuffer(const fmt::memory_buffer &buffer)
{
    m_LogFile.write(buffer.data(), buffer.size());
}

std::string LogManager::FormatTime(Timepoint time, const std::string pattern)
{
    // Put_time only works with c time point
    std::time_t cTime = std::chrono::system_clock::to_time_t(time);

    std::stringstream sstr;
    sstr << std::put_time(std::localtime(&cTime), pattern.c_str());
    return sstr.str();
}

} // namespace Sandbox
