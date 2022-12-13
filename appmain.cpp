#include "appmain.h"

#include <QDebug>

#include "windowservice/windowservice.h"
#include "systemservice/systemservice.h"
#include "utils/statisticlogger.h"

void AppMain::init()
{
    StatisticLogger::instance()->init();
    IpcTransceiver::instance()->init();
    AppManagerService::instance()->init();
    SystemService::instance()->init();

    WindowService::instance()->loadSimulationData(":/kpi.txt");

    connect(IpcTransceiver::instance(), &IpcTransceiver::sigClientConnectionChanged,
            this, &AppMain::onClientConnectionChanged);
    connect(WindowService::instance(), &WindowService::sigWindowLifeChanged,
            this, [](const QString &_window, bool _created) {
        if (_created)
            qDebug() << "+++ window:" << _window;
        else
            qDebug() << "--- window:" << _window;
    });
    connect(SystemService::instance(), &SystemService::sigMemoryUsageChanged,
            this, &AppMain::onMemoryUsageChanged);
}

void AppMain::sendInitData()
{
    AppManagerService::instance()->sendInitData();
    SystemService::instance()->sendInitData();
    WindowService::instance()->sendInitData();
}

void AppMain::clearTempData()
{
    SystemService::instance()->clearTempData();
    WindowService::instance()->clearTempData();
    AppManagerService::instance()->clearTempData();
}

void AppMain::clearAllData()
{
    SystemService::instance()->clearAllData();
    WindowService::instance()->clearAllData();
    AppManagerService::instance()->clearAllData();
}

void AppMain::onClientConnectionChanged(IpcTransceiver::IpcId _id, bool _isConnected)
{
    qDebug() << _id << _isConnected;

    if (_isConnected) {
        clearAllData();
        sendInitData();
    } else {
        StatisticLogger::instance()->stopLogging();
    }
}

void AppMain::onMemoryUsageChanged()
{
    const double used = SystemService::instance()->usedMemory();
    const double usedPercent = SystemService::instance()->usedPercentage();
    const auto level = SystemService::instance()->level();

    qDebug() << "RAM used:" << used << " (" << usedPercent << "%)";

    // level increased, or memory increased 5%
    if (usedPercent > m_lastMemoryUsagePercent + 5.0
            || level > m_lastMemoryLevel
            || level == SystemService::MemoryUsageLevel::High) {

        qWarning("Destroying windows by Memory policy");

        m_lastMemoryUsagePercent = usedPercent;

        AppManagerService::instance()->checkAndDestroyWindow();
        StatisticLogger::instance()->onWriteNeeded();
    }

    m_lastMemoryLevel = level;
}
