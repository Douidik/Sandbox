#ifndef SBX_LOG_MANAGER_HPP
#define SBX_LOG_MANAGER_HPP

#include "Misc/Clock.hpp"
#include <fmt/color.h>
#include <fmt/core.h>
#include <fstream>

namespace Sandbox
{

static const std::string s_LogMessagePattern = "[{time}] {message}\n";
static const std::string s_LogMessageTimePattern = "%T";
static const std::string s_LogFileTimePattern = "%d_%m_%y_at_%H_%M_%S";

namespace LogStyle
{

using namespace fmt;

const text_style INFO = fg(color::white);
const text_style WARN = fg(color::yellow);
const text_style ERROR = fg(color::orange);
const text_style CRITICAL = fg(color::red) | emphasis::bold;
const text_style DEBUG = fg(color::lime_green) | emphasis::underline;

} // namespace LogStyle

class LogManager
{
public:
    inline static void Init()
    {
        s_Instance = new LogManager();
    }
    inline static void Shut()
    {
        delete s_Instance;
    }
    static LogManager *GetInstance();

public:
    template <typename... Args>
    void Log(const fmt::text_style &style, const std::string message, Args &&...args)
    {
        fmt::memory_buffer buffer = FormatMessage(style, message, args...);
        PrintBuffer(style, buffer);
        WriteBuffer(buffer);
    }

private:
    LogManager();

    // Prints the message into the console
    void PrintBuffer(const fmt::text_style &style, const fmt::memory_buffer &buffer);
    // Writes the message into the logging file
    void WriteBuffer(const fmt::memory_buffer &buffer);

    template <typename... Args>
    fmt::memory_buffer FormatMessage(const fmt::text_style style, const std::string &message, Args &&...args)
    {
        using namespace fmt::literals;

        std::string time = FormatTime(Clock::GetTime(), s_LogMessageTimePattern);

        fmt::memory_buffer buffer;
        // We have to use fmt::format with an empty text_style because the other definition doesn't link
        // correctly. The text style is set when printing the buffer to the console
        std::string fmt = fmt::format(fmt::text_style(), message, args...);
        fmt::format_to(buffer, s_LogMessagePattern, "time"_a = time, "message"_a = fmt);

        return buffer;
    }

    std::string FormatTime(Timepoint time, const std::string pattern);

    std::ofstream m_LogFile;
    static LogManager *s_Instance;
};

} // namespace Sandbox

#define __SBX_LOG(style, ...)                                                                                \
    ::Sandbox::LogManager::GetInstance()->Log(::Sandbox::LogStyle::style, __VA_ARGS__)

#define SBX_INFO_LOG(...) __SBX_LOG(INFO, __VA_ARGS__)
#define SBX_WARN_LOG(...) __SBX_LOG(WARN, __VA_ARGS__)
#define SBX_ERROR_LOG(...) __SBX_LOG(ERROR, __VA_ARGS__)
#define SBX_CRITICAL_LOG(...) __SBX_LOG(CRITICAL, __VA_ARGS__)

#ifdef SBX_DEBUG_MODE
#define SBX_DEBUG_LOG(...) __SBX_LOG(DEBUG, __VA_ARGS__)
#endif

#endif
