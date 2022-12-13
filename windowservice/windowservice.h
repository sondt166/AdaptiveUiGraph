#ifndef WINDOWSERVICE_H
#define WINDOWSERVICE_H

#include <QString>
#include <QTimer>
#include <QMap>

#include "../systemservice/systemservice.h"
#include "utils/singleton.h"

class LaunchInfo {
public:
    int launchedTimes() const { return nLaunches; }
    int createTimes() const { return nCreate; }
    int destroyTimes() const { return nDestroy; }
    int launchTimesAfterLastCreation() const { return nLaunchesAfterLastCreation; }
    double averaged() const { return nLaunches == 0 ? 0.0 : (accumulated / nLaunches); }
    double accumulatedLaunchTime() const { return accumulated; }

    void addRecord(double _launchTime, bool _recreateWindow) {
        nLaunches++;
        accumulated += _launchTime;

        if (_recreateWindow) {
            nCreate += 1;
        } else {
            // nLaunchesAfterLastCreation++;
        }
    }
    void addDestroyRecord() {
        nDestroy++;
        nLaunchesAfterLastCreation = 0;
    }
    void prepareToIncreaseInternalMemory() {
        nLaunchesAfterLastCreation++;
    }
    void clear() { nLaunches = 0; accumulated = 0.0; nCreate = 0; nDestroy = 0; }

private:
    int nLaunches {0};
    int nCreate {0};
    int nDestroy {0};
    int nLaunchesAfterLastCreation {0};
    double accumulated {0.0};
};

class WindowService : public QObject
{
    Q_OBJECT
    MAKE_SINGLETON(WindowService);
public:

    using WindowType = SystemService::MemoryUsageType;

    void clearAllData();
    void clearTempData();
    void sendInitData();
    void loadSimulationData(const QString &_filePath);

    void launchWindow(WindowType _type, const QString &_windowName, bool _openWhenAlreadyOnForeground);
    void createWindow(WindowType _type, const QString &_windowName);
    void increaseWindowMemoryUsaged(WindowType _type, const QString &_windowName);
    void destroyWindow(const QString &_windowName);

    bool isWindowCreated(const QString &_windowName) const;
    bool isWindowCreatedAtleastOnce(const QString &_windowName) const;

    QStringList createdWindows() const;

    LaunchInfo windowLaunchInfo(const QString &_windowName) const;
    QMap<QString, LaunchInfo> windowLaunchInfo() const;
    double totalLaunchTime() const;

signals:
    void sigWindowLifeChanged(const QString &_windowName, bool _created);

private slots:

private:
    QStringList m_createdWindows {};
    QStringList m_windowsCreatedAtleastOnce {};

    // launch without creating window (the window was not destoryed before)
    static double m_kNormalWindowLauchKpi;

    struct WindowLaunchKpi {
        double firstCreation;
        double normalCreation;  // after the first creation
        double memoryUsageBase;     // unit: MB
        double memoryUsagePeak;     // unit: MB
        double memoryUsageCurrent;     // unit: MB
    };

    QMap<QString, WindowLaunchKpi> m_windowKpi {}; // load from file
    QMap<QString, LaunchInfo> m_windowLaunchInfo {}; // collect over time
    QMap<QString, WindowType> m_windowType {}; // collect over time

    SystemService *m_system {SystemService::instance()};
};

#endif // WINDOWSERVICE_H
