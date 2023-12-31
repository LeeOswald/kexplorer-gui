#pragma once

#include <kxclient/log.hpp>

#include <QString>

#include <deque>
#include <functional>
#include <mutex>


class Logger final
    : public Kx::Log::ILog
{
public:
    using Delegate = std::function<void(QString)>;

    explicit Logger(Kx::Log::Level level) noexcept
        : m_level(level)
    {}

    void setLevel(Kx::Log::Level l) noexcept
    {
        m_level = l;
    }

    void setDelegate(Delegate d) noexcept;

    Kx::Log::Level level() const noexcept override
    {
        return m_level;
    }

    bool writev(Kx::Log::Level level, const char* format, va_list args) noexcept override;
    bool write(Kx::Log::Level level, const char* format, ...) noexcept override;

private:
    struct Saved
    {
        Kx::Log::Level level = Kx::Log::Level::Debug;
        QString msg;

        Saved() = default;
        Saved(Kx::Log::Level level, QString msg) : level(level), msg(msg) {}
    };

    void write(Kx::Log::Level level, const std::string& text);
    void save(Kx::Log::Level level, QString msg);

    std::mutex m_mutex;
    Kx::Log::Level m_level;
    Delegate m_delegate;
    std::deque<Saved> m_saved;
    static const size_t kMaxSavedMessages = 65536;
};

