#include "statisticlogger.h"

#include <QDebug>
#include <QDir>
#include "windowservice/windowservice.h"
#include "systemservice/systemservice.h"

void StatisticLogger::init()
{
    connect(&m_writeTimer, &QTimer::timeout, this, &StatisticLogger::onWriteNeeded);
    m_writeTimer.setInterval(5000);
}

void StatisticLogger::startLogging()
{
    qDebug("Start");

    m_folderName = dataDir();
    qDebug() << "data dir: " << m_folderName;

    // clear the folder if existed
    QDir(m_folderName).removeRecursively();
    QDir(".").mkpath(m_folderName);

    m_fgraph.reset(new QFile(m_folderName + "graph.md"));
    m_fmemory.reset(new QFile(m_folderName + "memory.csv"));
    m_fkpi.reset(new QFile(m_folderName + "kpi.csv"));
    m_fkpiTotal.reset(new QFile(m_folderName + "kpi_total.csv"));

    addHeader();
    onWriteNeeded();

    m_writeTimer.start();
}

void StatisticLogger::stopLogging()
{
    qDebug("Stop");
    m_writeTimer.stop();
}

bool StatisticLogger::isRunning() const
{
    return m_writeTimer.isActive();
}

void StatisticLogger::updateGraph(const std::string &_content)
{
    if (!m_fgraph)
        return;

    if (!m_fgraph->open(QFile::WriteOnly)) {
        qCritical("Cannot open file");
        return;
    }

    m_fgraph->write(_content.c_str());
    m_fgraph->close();
}

QString StatisticLogger::dataDir()
{
    return "./data/" + QDateTime::currentDateTime().toString("MMdd-HH_mm") + "/";
}

void StatisticLogger::addHeader()
{
    if (m_fmemory && m_fmemory->open(QFile::WriteOnly)) {
        m_fmemory->write(QString("%1,%2,%3,%4,%5\r\n")
                         .arg("Time")
                         .arg("UsedStatic")
                         .arg("UsedNonStatic")
                         .arg("Total")
                         .arg("Level")
                         .toLocal8Bit());
        m_fmemory->close();
    }

    if (m_fkpiTotal && m_fkpiTotal->open(QFile::WriteOnly)) {
        m_fkpiTotal->write(QString("%1,%2\r\n")
                         .arg("Time")
                         .arg("TotalDelay")
                         .toLocal8Bit());
        m_fkpiTotal->close();
    }
}

void StatisticLogger::onWriteNeeded()
{
    QString now = QDateTime::currentDateTime().toString("HH:mm:ss");

    if (m_fmemory && m_fmemory->open(QFile::Append)) {
        double usedStatic = SystemService::instance()
                ->usedMemory(SystemService::MemoryUsageType::Static);
        double usedNonStatic = SystemService::instance()
                ->usedMemory(SystemService::MemoryUsageType::NonStatic);

        double total = SystemService::instance()->totalMemory();
        double level = SystemService::instance()->level();

        m_fmemory->write(QString("%1,%2,%3,%4,%5\r\n")
                         .arg(now)
                         .arg(usedStatic)
                         .arg(usedNonStatic)
                         .arg(total)
                         .arg(level)
                         .toLocal8Bit());
        m_fmemory->close();
    }

    if (m_fkpi && m_fkpi->open(QFile::WriteOnly)) {
        m_fkpi->write(QString("%1,%2,%3,%4,%5,%6\r\n")
                         .arg("Role")
                         .arg("KPI Averaged")
                         .arg("KPI Sum")
                         .arg("Launched times")
                         .arg("Create times")
                         .arg("Destroy times")
                         .toLocal8Bit());

        auto map = WindowService::instance()->windowLaunchInfo();
        for (const auto &k : map.keys()) {
            const auto item = map[k];
            m_fkpi->write(QString("%1,%2,%3,%4,%5,%6\r\n")
                             .arg(k)
                             .arg(item.averaged())
                             .arg(item.accumulatedLaunchTime())
                             .arg(item.launchedTimes())
                             .arg(item.createTimes())
                             .arg(item.destroyTimes())
                             .toLocal8Bit());
        }
        m_fkpi->close();
    }

    if (m_fkpiTotal && m_fkpiTotal->open(QFile::Append)) {
        double totalDelay = WindowService::instance()->totalLaunchTime();

        m_fkpiTotal->write(QString("%1,%2\r\n")
                         .arg(now)
                         .arg(totalDelay)
                         .toLocal8Bit());
        m_fkpiTotal->close();
    }
}
