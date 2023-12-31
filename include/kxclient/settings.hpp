#pragma once

#include <kxclient/qvariantconverter.hpp>


namespace Kx
{
    
struct ISettingsStorage
{
    virtual QStringList keys() = 0;
    virtual QVariant get(std::string_view key, const QVariant& defaultValue = QVariant()) = 0;
    virtual void set(std::string_view key, const QVariant& value) = 0;
    virtual void sync() = 0;

protected:
    virtual ~ISettingsStorage() {}
};    
    

class OptionBase
{
public:
    static QVariant get(ISettingsStorage* storage, std::string_view key, const QVariant& defaultValue = QVariant())
    {
        return storage->get(key, defaultValue);
    }

    static void set(ISettingsStorage* storage, std::string_view key, const QVariant& value)
    {
        storage->set(key, value);
    }
};


template <typename T>
class Option
    : public OptionBase
{
public:
    static T get(ISettingsStorage* storage, std::string_view key, const T& defaultValue)
    {
        return Kx::QVariantConvertor<T>::convert(OptionBase::get(storage, key, defaultValue));
    }

    static void set(ISettingsStorage* storage, std::string_view key, const T& value)
    {
        OptionBase::set(storage, key, Kx::QVariantConvertor<T>::convert(value));
    }
};


    
} // namespace Kx {}
