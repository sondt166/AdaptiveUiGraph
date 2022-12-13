#include <QCoreApplication>
#include "loghandler.h"

#include "appmain.h"

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    initLog();

    AppMain::instance()->init();
    return app.exec();
}
