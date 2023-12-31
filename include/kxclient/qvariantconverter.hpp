#pragma once

#include <kxclient/kxclient.hpp>

#include <QVariant>

namespace Kx
{
 
template <typename T>
class QVariantConvertor;


namespace __
{

template <typename T>
class QVariantConvertorBase
{
public:
    static QVariant convert(const T& v) { return QVariant(v); }
};

} // namespace __ {}


template <>
class QVariantConvertor<bool>
    : public __::QVariantConvertorBase<bool>
{
public:
    static bool convert(const QVariant& v) { return v.toBool(); }
};

template <>
class QVariantConvertor<int>
    : public __::QVariantConvertorBase<int>
{
public:
    static int convert(const QVariant& v) { return v.toInt(); }
};

template <>
class QVariantConvertor<unsigned>
    : public __::QVariantConvertorBase<unsigned>
{
public:
    static unsigned int convert(const QVariant& v) { return v.toUInt(); }
};

template <>
class QVariantConvertor<long long>
    : public __::QVariantConvertorBase<long long>
{
public:
    static long long convert(const QVariant& v) { return v.toLongLong(); }
};

template <>
class QVariantConvertor<unsigned long long>
    : public __::QVariantConvertorBase<unsigned long long>
{
public:
    static unsigned long long convert(const QVariant& v) { return v.toULongLong(); }
};

template <>
class QVariantConvertor<QString>
    : public __::QVariantConvertorBase<QString>
{
public:
    static QString convert(const QVariant& v) { return v.toString(); }
};

template <>
class QVariantConvertor<QStringList>
    : public __::QVariantConvertorBase<QStringList>
{
public:
    static QStringList convert(const QVariant& v) { return v.toStringList(); }
};

template <>
class QVariantConvertor<QByteArray>
    : public __::QVariantConvertorBase<QByteArray>
{
public:
    static QByteArray convert(const QVariant& v) { return v.toByteArray(); }
};
 
    
} // namespace Kx {}
