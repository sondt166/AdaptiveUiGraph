#ifndef THROTTLER_H
#define THROTTLER_H

#include <QTimer>
#include <QDateTime>

class Throttler : public QObject
{
    Q_OBJECT
public:
    Throttler(int throttleInterval = 500)
        : QObject(nullptr),
          m_throttleInterval(throttleInterval) {
        m_throttleTimer.setSingleShot(true);
        m_throttleTimer.setInterval(throttleInterval);

        connect(&m_throttleTimer, &QTimer::timeout,
                this, &Throttler::onThrottleTimeout);
    }

    void trigger() {
        const auto current = currentTimestamp();
        if (current >= m_lastTrigger + m_throttleInterval) {
            m_throttleTimer.stop();
            fire();
        } else {
            m_throttleTimer.start();
        }
    }

signals:
    void sigActionTriggered();

private slots:
    void onThrottleTimeout() {
        fire();
    }

private:
    static qint64 currentTimestamp() {
        return QDateTime::currentMSecsSinceEpoch();
    }

    void fire() {
        emit sigActionTriggered();
        m_lastTrigger = currentTimestamp();
    }

private:
    int m_throttleInterval {1000};
    qint64 m_lastTrigger {};

    QTimer m_throttleTimer {};
};

#endif // THROTTLER_H
