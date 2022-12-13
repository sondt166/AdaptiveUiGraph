#include "systemservice.h"
#include "appservice/interface/service/BaseAppDeploy.h" // reuse deployer

void SystemService::sendInitData() const
{
    m_memoryDeployThrottler.trigger();
}

void SystemService::useMemory(MemoryUsageType _type, double _MB)
{
    auto &used= m_usedMemory[_type];
    used += _MB;

    if (usedMemory() > totalMemory()) {
        qCritical("OUT OF MEMORY!!!");
    }

    emit sigMemoryUsageChanged();
    m_memoryDeployThrottler.trigger();
    setMemoryLevel(level());
}

void SystemService::freeMemory(MemoryUsageType _type, double _MB)
{
    if (_type == MemoryUsageType::Static) {
        qFatal("WHYYYYY");
    }
    auto &used= m_usedMemory[_type];
    used -= _MB;

    if (used < 0) used = 0;

    emit sigMemoryUsageChanged();
    m_memoryDeployThrottler.trigger();
    setMemoryLevel(level());
}

double SystemService::totalMemory() const
{
    return 1.0 * 1024.0; // 8GB
}

double SystemService::usedMemory() const
{
    double usedSum = 0;
    for (const auto item : m_usedMemory) {
        usedSum += item;
    }
    return usedSum;
}

double SystemService::usedPercentage() const
{
    return 100.0 * usedMemory() / totalMemory();
}

SystemService::MemoryUsageLevel SystemService::level() const
{
    auto percent = usedPercentage();

    if (percent < 70)
        return MemoryUsageLevel::Medium1;
    if (percent < 80)
        return MemoryUsageLevel::Medium2;
    if (percent < 90)
        return MemoryUsageLevel::Medium3;

    return MemoryUsageLevel::High;
}

double SystemService::usedMemory(MemoryUsageType _type) const
{
    return m_usedMemory[_type];
}

void SystemService::setMemoryLevel(MemoryUsageLevel level)
{
    if (level == m_level)
        return;

    m_level = level;
    emit sigMemoryLevelChanged();
}

void SystemService::init()
{
    connect(&m_memoryDeployThrottler, &Throttler::sigActionTriggered,
            this, [&](){
        BaseAppDeploy::instance()->onBrSystemMemoryChanged(
                    usedMemory(MemoryUsageType::Static),
                    usedMemory(MemoryUsageType::NonStatic),
                    totalMemory()
                    );
    BaseAppDeploy::instance()->onBrMemoryLevelChanged((int)level());
    });
}

void SystemService::clearTempData()
{
    m_usedMemory.clear();
}

void SystemService::clearAllData()
{
    clearTempData();
}
