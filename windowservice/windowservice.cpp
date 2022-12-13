#include "windowservice.h"
#include "appservice/interface/service/BaseAppDeploy.h" // reuse deployer
#include "appservice/appmanagerservice.h"

#include <QDebug>
#include <QFile>

double WindowService::m_kNormalWindowLauchKpi {0.1};

void WindowService::sendInitData()
{
    BaseAppDeploy::instance()->onBrTotalKpiChanged(totalLaunchTime());
}

void WindowService::loadSimulationData(const QString &_filePath)
{
    // qDebug();
    QFile f(_filePath);

    if (!f.exists()) {
        qCritical() << "KPI file not found";
        return;
    }
    if (!f.open(QFile::ReadOnly)) {
        qCritical() << "KPI file open failed";
        return;
    }

    m_windowKpi.clear();

    while (!f.atEnd()) {
        auto line = f.readLine();
        auto cols = QString(line).simplified().split(" ");

        if (cols.size() != 5) {
            qCritical("Column count is not matched! expecting 4, but provided %d", cols.size());
            break;
        }

        auto winName = cols[0];
        auto memBase = cols[1].toDouble() / 1024.0;
        auto memPeak = cols[2].toDouble() / 1024.0;
        auto firstCreationKpi = cols[3].toDouble();
        auto normalCreationKpi = cols[4].toDouble();

        auto &window = m_windowKpi[winName];
        window.firstCreation = firstCreationKpi / 1000.0;
        window.normalCreation = normalCreationKpi / 1000.0;
        window.memoryUsageBase = memBase;
        window.memoryUsagePeak = memPeak;

        // qDebug() << winName << " " << mem << " " << firstCreationKpi << " " << normalCreationKpi;
    }

    f.close();
}

void WindowService::launchWindow(WindowType _type, const QString &_windowName, bool _openWhenAlreadyOnForeground)
{
    if (_windowName.isEmpty()) {
        qWarning("Bad window name");
        return;
    }
    m_windowType[_windowName] = _type;

    // if the window has not been destroyed, use normal KPI (100ms)
    double launchTime = m_kNormalWindowLauchKpi;
    const bool windowCreated = isWindowCreated(_windowName);
    bool recreateWindow = false;

    // if the window has not been created, create it
    if (!windowCreated) {
        recreateWindow = true;

        if (m_windowKpi.contains(_windowName)) {

            if (isWindowCreatedAtleastOnce(_windowName)) {
                launchTime = m_windowKpi[_windowName].normalCreation;
            } else {
                launchTime = m_windowKpi[_windowName].firstCreation;
            }

        } else {
            qCritical() << "KPI data for " << _windowName << " is not found";
        }

        createWindow(_type, _windowName);
    } else {
        if (_openWhenAlreadyOnForeground) {
            m_windowLaunchInfo[_windowName].prepareToIncreaseInternalMemory();
            increaseWindowMemoryUsaged(_type, _windowName);
        }
    }

    m_windowLaunchInfo[_windowName].addRecord(launchTime, recreateWindow);

    qDebug() << "Launch time: " << launchTime << " for " << _windowName << ", total=" << totalLaunchTime();

    BaseAppDeploy::instance()->onBrTotalKpiChanged(totalLaunchTime());
}

void WindowService::createWindow(WindowType _type, const QString &_windowName)
{
    if (_windowName.isEmpty())
        return;

    if (isWindowCreated(_windowName))
        return;

    m_createdWindows.append(_windowName);

    // save the window to `created at least once` history
    if (!isWindowCreatedAtleastOnce(_windowName)) {
        m_windowsCreatedAtleastOnce.append(_windowName);
    }

    emit sigWindowLifeChanged(_windowName, true);
    /*
    BaseAppDeploy::instance()->onBrWindowLifeStatusChanged(cstr(_windowName),
                                                           true,
                                                           AppManagerService::instance()->rolesThatUseWindow(_windowName));
    */

    if (m_windowKpi.contains(_windowName)) {
        const auto memory = m_windowKpi[_windowName].memoryUsageBase;
        m_windowKpi[_windowName].memoryUsageCurrent = m_windowKpi[_windowName].memoryUsageBase;
        m_system->useMemory(_type, memory);
    } else {
        qCritical() << "Memory usage data for \"" << _windowName << "\" is not found";
    }
}

void WindowService::increaseWindowMemoryUsaged(WindowType _type, const QString &_windowName)
{
    if (_windowName.isEmpty())
        return;

    if (!isWindowCreated(_windowName))
        return;

    if (m_windowKpi.contains(_windowName)) {
        const auto baseMemory = m_windowKpi[_windowName].memoryUsageBase;
        const auto peakMemory = m_windowKpi[_windowName].memoryUsagePeak;
        const auto nLaunchesAfterLastCreation = m_windowLaunchInfo[_windowName].launchTimesAfterLastCreation();

        // increase 10% each time
        const auto step = 0.1;
        auto currentMemory = baseMemory * (1.0 + nLaunchesAfterLastCreation * step);

        if (currentMemory > peakMemory)
            currentMemory = peakMemory;

        m_windowKpi[_windowName].memoryUsageCurrent = currentMemory;

        auto delta = currentMemory - baseMemory;

        if (delta > 0.0) {
            qDebug() << "Expand " << delta << "MB for" << _windowName
                     << baseMemory
                     << currentMemory
                     << peakMemory;
            m_system->useMemory(_type, delta);
        }
        // if (delta < 0) {
            // m_system->freeMemory(_type, delta);
        // }

    } else {
        qCritical() << "Memory usage data for \"" << _windowName << "\" is not found";
    }
}

void WindowService::destroyWindow(const QString &_windowName)
{
    if (_windowName.isEmpty())
        return;

    if (!isWindowCreated(_windowName))
        return;

    m_createdWindows.removeAll(_windowName);
    if (!m_windowType.contains(_windowName)) {
        qCritical() << _windowName << "does not exist in windowType";
        // qFatal("Not existed");
        return;
    }
    m_windowLaunchInfo[_windowName].addDestroyRecord();
    const auto type = m_windowType[_windowName];

    emit sigWindowLifeChanged(_windowName, false);
    /*
    BaseAppDeploy::instance()->onBrWindowLifeStatusChanged(cstr(_windowName),
                                                           false,
                                                           AppManagerService::instance()->rolesThatUseWindow(_windowName));
    */

    if (m_windowKpi.contains(_windowName)) {
        const auto memory = m_windowKpi[_windowName].memoryUsageCurrent;
        qDebug() << _windowName << memory;
        m_system->freeMemory(type, memory);
    } else {
        qCritical() << "Memory usage data for \"" << _windowName << "\" is not found";
    }
}

bool WindowService::isWindowCreated(const QString &_windowName) const
{
    return m_createdWindows.contains(_windowName);
}

bool WindowService::isWindowCreatedAtleastOnce(const QString &_windowName) const
{
    return m_windowsCreatedAtleastOnce.contains(_windowName);
}

QStringList WindowService::createdWindows() const
{
    return m_createdWindows;
}

LaunchInfo WindowService::windowLaunchInfo(const QString &_windowName) const
{
    return m_windowLaunchInfo[_windowName];
}

QMap<QString, LaunchInfo> WindowService::windowLaunchInfo() const
{
    return m_windowLaunchInfo;
}

double WindowService::totalLaunchTime() const
{
    double sum = 0;
    for (const auto & window : m_windowLaunchInfo) {
        sum += window.accumulatedLaunchTime();
    }
    return sum;
}

void WindowService::clearAllData()
{
    clearTempData();
    // m_windowKpi.clear();
}

void WindowService::clearTempData()
{
    qWarning();
    m_createdWindows.clear();
    m_windowsCreatedAtleastOnce.clear();
    m_windowLaunchInfo.clear();
}
