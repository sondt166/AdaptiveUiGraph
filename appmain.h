#ifndef APPMAIN_H
#define APPMAIN_H

#include <QObject>

#include "ipc/ipctransceiver.h"
#include "appservice/appmanagerservice.h"
#include "systemservice/systemservice.h"
#include "utils/singleton.h"

class AppMain : public QObject
{
    Q_OBJECT
    MAKE_SINGLETON(AppMain);
public:
    void init();
    void sendInitData();
    void clearTempData();
    void clearAllData();

private:

signals:

private slots:
    void onClientConnectionChanged(IpcTransceiver::IpcId _id, bool _isConnected);
    void onMemoryUsageChanged();

private:
    double m_lastMemoryUsagePercent {0};
    SystemService::MemoryUsageLevel m_lastMemoryLevel {};
};

#endif // APPMAIN_H
