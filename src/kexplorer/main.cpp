#include "kexplorer-version.h"

#include <QCoreApplication>
#include <QMessageBox>

#if defined(_MSC_VER) && defined(_DEBUG)
#include <crtdbg.h>
#endif



int main(int argc, char *argv[])
{
#if defined(_MSC_VER) && defined(_DEBUG)
    int tmpFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
    tmpFlag |= _CRTDBG_LEAK_CHECK_DF;
    _CrtSetDbgFlag(tmpFlag);
#endif

    QCoreApplication a(argc, argv);
    a.setApplicationName(KX_APPLICATION_NAME);
    a.setApplicationVersion(QString("%1.%2.%3").arg(KX_VERSION_MAJOR).arg(KX_VERSION_MINOR).arg(KX_VERSION_PATCH));
    a.setOrganizationName(KX_ORGANIZATION_NAME);

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


