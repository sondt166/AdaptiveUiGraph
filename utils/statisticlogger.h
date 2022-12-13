#ifndef STATISTICLOGGER_H
#define STATISTICLOGGER_H

#include <QObject>
#include <QDateTime>
#include <QFile>
#include <QTimer>
#include <QScopedPointer>

#include "windowservice/windowservice.h"
#include "singleton.h"

class StatisticLogger : public QObject
{
    Q_OBJECT
    MAKE_SINGLETON(StatisticLogger);

public:
    void init();
    void startLogging();
    void stopLogging();
    bool isRunning() const;

    void updateGraph(const std::string &_content);

signals:

public slots:
    void onWriteNeeded();

private:
    static QString dataDir();
    void addHeader();

private:
    QScopedPointer<QFile> m_fgraph {};
    QScopedPointer<QFile> m_fmemory {};
    QScopedPointer<QFile> m_fkpi {};
    QScopedPointer<QFile> m_fkpiTotal {};

    QString m_folderName {};

    QTimer m_writeTimer {this};
};

#endif // STATISTICLOGGER_H
