#pragma once

#include <kxclient/settings.hpp>

#include <QSettings>


class Settings final
    : public Kx::ISettingsStorage
{
public:
    QStringList keys() override
    {
        return storage().allKeys();
    }

    QVariant get(std::string_view key, const QVariant& defaultValue = QVariant()) override
    {
        return storage().value(key, defaultValue);
    }

    void set(std::string_view key, const QVariant& value) override
    {
        storage().setValue(key, value);
    }

    void sync() override
    {
        storage().sync();
    }

private:
    static QSettings& storage()
    {
        static QSettings s;
        return s;
    }
};

