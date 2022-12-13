#ifndef SYSTEMSERVICE_H
#define SYSTEMSERVICE_H

#include <QObject>
#include <QMap>
#include <QTimer>

#include "utils/singleton.h"
#include "utils/throttler.h"

class SystemService : public QObject
{
    Q_OBJECT
    MAKE_SINGLETON(SystemService);
public:
    enum MemoryUsageLevel {
        Medium1, // destroy nothing
        Medium2, // destroy inactive nodes
        Medium3, // destroy potentials
        High     // only keep foreground
    };

    enum MemoryUsageType {
        Static,
        NonStatic
    };

    void init();
    void clearTempData();
    void clearAllData();
    void sendInitData() const;

    void useMemory(MemoryUsageType _type, double _MB);
    void freeMemory(MemoryUsageType _type, double _MB);

    double totalMemory() const;
    /**
     * @brief Used memory in general of all types
     */
    double usedMemory() const;
    double usedPercentage() const;
    MemoryUsageLevel level() const;

    /**
     * @brief Memory usage per type
     */
    double usedMemory(MemoryUsageType _type) const;

private:
    void setMemoryLevel(MemoryUsageLevel level);

signals:
    void sigMemoryUsageChanged();
    void sigMemoryLevelChanged();

private:
    QMap<MemoryUsageType, double> m_usedMemory {}; // unit: MegaBytes
    MemoryUsageLevel m_level {};
    mutable Throttler m_memoryDeployThrottler {};
};

#endif // SYSTEMSERVICE_H
