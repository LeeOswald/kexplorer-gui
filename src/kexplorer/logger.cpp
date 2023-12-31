#include "logger.hpp"

#include <QDateTime>


void Logger::setDelegate(Delegate d) noexcept
{
    std::lock_guard l(m_mutex);
    m_delegate = d;

    // send any saved messages to the delegate
    if (m_delegate)
    {
        while (!m_saved.empty())
        {
            auto& saved = m_saved.front();

            if (saved.level >= m_level)
                m_delegate(saved.msg);

            m_saved.pop_front();
        }
    }
}

bool Logger::writev(Kx::Log::Level level, const char* format, va_list args) noexcept
{
    if (level < m_level)
        return true;

    if (!format || !*format)
        return true;

    va_list args1;
    va_copy(args1, args);
    va_list args2;
    va_copy(args2, args);

    auto required = ::vsnprintf(nullptr, 0, format, args1);
    std::string buffer;
    buffer.resize(required);
    ::vsnprintf(buffer.data(), required + 1, format, args);

    va_end(args1);
    va_end(args2);

    write(level, buffer);

    return true;
}

bool Logger::write(Kx::Log::Level level, const char* format, ...) noexcept
{
    if (level < m_level)
        return true;

    if (!format || !*format)
        return true;

    va_list args;
    va_start(args, format);

    auto b = writev(level, format, args);

    va_end(args);

    return b;
}

void Logger::write(Kx::Log::Level level, const std::string& text)
{
    const char* flag = "?";
    switch (level)
    {
    case Kx::Log::Level::Debug: flag = "D"; break;
    case Kx::Log::Level::Info: flag = "I"; break;
    case Kx::Log::Level::Warning: flag = "W"; break;
    case Kx::Log::Level::Error: flag = "E"; break;
    case Kx::Log::Level::Fatal: flag = "F"; break;
    default: break;
    }

#if KX_WINDOWS
    auto tid = ::GetCurrentThreadId();
#elif KX_LINUX
    auto tid = ::gettid();
#endif

    auto time = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
    auto msg = QString("[%1 %2 @%3] %4").arg(time, QString(flag), QString::fromLocal8Bit(std::to_string(tid).c_str()), QString::fromLocal8Bit(text.c_str(), text.length()));

    std::lock_guard l(m_mutex);

    if (m_delegate)
        m_delegate(msg);
    else
        save(level, msg); // keep messages until m_delegate is available

#if KX_WINDOWS && defined(_DEBUG)
    msg.append(L'\n');
    ::OutputDebugStringW(reinterpret_cast<const WCHAR*>(msg.utf16()));
#endif
}

void Logger::save(Kx::Log::Level level, QString msg)
{
    while (m_saved.size() + 1 > kMaxSavedMessages)
        m_saved.pop_front();

    m_saved.emplace_back(level, msg);
}
