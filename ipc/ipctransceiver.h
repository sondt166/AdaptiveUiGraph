#ifndef IPCTRANSCEIVER_H
#define IPCTRANSCEIVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QJsonObject>
#include <QTimer>

class IpcTransceiver : public QObject
{
    Q_OBJECT
public:
    enum IpcId {
        IpcId_Unknown = -1,
        IpcId_Server,
        IpcId_Home,
    };
    Q_ENUM(IpcId);

    struct Peer {
        IpcId id;
        QTcpSocket *socket;

        bool operator==(const Peer &rhs) {
            return id == rhs.id
                    && socket == rhs.socket;
        }
    };

    static IpcTransceiver *instance();
    void init(IpcId id = IpcId_Server);

    void broadcast(const QJsonObject &obj);
    void send(const QJsonObject &obj, IpcId targetId = IpcId_Server);
    void send(const QJsonObject &obj, QTcpSocket *socket);
    bool isClientConnected(IpcId id);
    IpcId lastSender() const;

    QJsonObject header(int function);

signals:
    bool sigHandleMessage(const QJsonObject &obj);
    void sigServerConnectionChanged(bool connected);
    void sigClientConnectionChanged(IpcTransceiver::IpcId &id, bool connected);

private slots:
    void onNewConnection();
    void onSocketStateChanged(QAbstractSocket::SocketState state);
    void onReadyRead();
    void onReconnectTimer();

private:
    IpcTransceiver();
    bool isServer() { return m_id == IpcId_Server; }
    void registerToServer();
    void handleMessage(QTcpSocket *sender, const QJsonObject &obj);

    IpcId m_id;
    IpcId m_lastSender;

    bool m_initialized;

    QTcpServer *m_server;
    QTcpSocket *m_client;
    QList<Peer> m_peers;

    QTimer m_reconnectTimer;
    int m_sendPacketId;
    int m_lastReceivePacketId;
};

Q_DECLARE_METATYPE(IpcTransceiver::IpcId);

#endif // IPCTRANSCEIVER_H
