#include "kexplorer-version.h"

#include "logger.hpp"
#include "settings.hpp"

#include <QCoreApplication>
#include <QMessageBox>

#if defined(_MSC_VER) && KX_DEBUG
#include <crtdbg.h>
#endif



int main(int argc, char *argv[])
{
#if defined(_MSC_VER) && KX_DEBUG
    int tmpFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
    tmpFlag |= _CRTDBG_LEAK_CHECK_DF;
    _CrtSetDbgFlag(tmpFlag);
#endif

    QCoreApplication a(argc, argv);
    a.setApplicationName(KX_APPLICATION_NAME);
    a.setApplicationVersion(QString("%1.%2.%3").arg(KX_VERSION_MAJOR).arg(KX_VERSION_MINOR).arg(KX_VERSION_PATCH));
    a.setOrganizationName(KX_ORGANIZATION_NAME);

    Settings settings;
    auto logLevel = static_cast<Kx::Log::Level>(Kx::Option<int>::get(&settings, "log/level", int(Kx::Log::Level::Off)));
    Logger logger(logLevel);

    try
    {

        return a.exec();
    }
    catch (std::exception& e)
    {
        QMessageBox::critical(nullptr, QString::fromLocal8Bit(KX_APPLICATION_NAME), QLatin1String("Unexpected error"), QMessageBox::Ok);
    }

    return EXIT_FAILURE;
}


