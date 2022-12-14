#include "ipctransceiver.h"

#include <QJsonDocument>
#include <QJsonValue>
#include <QTimer>

#include <iostream>

#define TCP_IP_ADDR "127.0.0.1"
#define TCP_PORT    50000

#define PACKET_SEPERATOR "\n\n"

IpcTransceiver::IpcTransceiver()
        : m_id(IpcId_Unknown),
          m_lastSender(IpcId_Unknown),
          m_initialized(false),
          m_server(),
          m_client(),
          m_peers(),
          m_reconnectTimer(this),
          m_sendPacketId(0),
          m_lastReceivePacketId(-1)
{
    qRegisterMetaType<IpcId>();

    connect(&m_reconnectTimer, &QTimer::timeout, this, &IpcTransceiver::onReconnectTimer);

    m_reconnectTimer.setInterval(5000);
}

void IpcTransceiver::registerToServer()
{
    Q_ASSERT(!isServer());
    // qDebug("registering...");

    QJsonObject obj = header(0);
    obj["action"] = "register";

    send(obj);
}

void IpcTransceiver::handleMessage(QTcpSocket *sender, const QJsonObject &obj)
{
    const IpcId sender_id = (IpcId)obj.value("sender_id").toInt();

    // register request from client
    if (obj.value("action").toString() == "register") {

        auto p = std::find_if(m_peers.begin(), m_peers.end(), [sender](const Peer &i) {
            return i.socket == sender;
        });

        if (p != m_peers.end()) {
            p->id = sender_id;
            qDebug() << "Peer" << p->id << "registered!";
            emit sigClientConnectionChanged(p->id, true);
        }

        return;
    }

    // qDebug() << "message from" << sender_id;
    m_lastSender = sender_id; // saved to respond later
    emit sigHandleMessage(obj);
}

IpcTransceiver *IpcTransceiver::instance()
{
    static IpcTransceiver *_instance = nullptr;
    if (_instance == nullptr) {
        _instance = new IpcTransceiver();
    }
    return _instance;
}

void IpcTransceiver::init(IpcId id)
{
    if (m_initialized) {
        qWarning("already initialized");
        return;
    }
    m_initialized = true;

    m_id = id;

    if (id == IpcId_Server) {
        m_server = new QTcpServer(this);
        m_server->listen(QHostAddress::Any, TCP_PORT);
        connect(m_server, &QTcpServer::newConnection, this, &IpcTransceiver::onNewConnection);

        // qDebug() << "Server is listening on port:" << TCP_PORT;
    } else {
        m_client = new QTcpSocket(this);
        connect(m_client, &QTcpSocket::readyRead, this, &IpcTransceiver::onReadyRead);
        connect(m_client, &QTcpSocket::stateChanged, this, &IpcTransceiver::onSocketStateChanged);

        m_client->connectToHost(QHostAddress(TCP_IP_ADDR), TCP_PORT);
        // qDebug() << "Connecting to server on port:" << TCP_PORT;
    }
}

void IpcTransceiver::broadcast(const QJsonObject &obj)
{
    Q_ASSERT_X(isServer(), __func__, "You are not server!");

    // send to self
    send(obj, m_id);

    for (auto & p : m_peers) {
        if (!p.socket->isWritable()) {
            qCritical() << "socket" << p.id << "is not writeable";
            return;
        }
        send(obj, p.socket);
    }
}

void IpcTransceiver::send(const QJsonObject &obj, IpcId targetId)
{
    // only server can send to target, clients can only send to server
    Q_ASSERT_X(m_id == IpcId_Server || targetId == IpcId_Server, __func__, "You are not server!");

    if (targetId == m_id) {
        // sending to itself
        handleMessage(nullptr, obj);
        return;
    }

    if (isServer()) {
        Q_ASSERT(m_server != nullptr);

        auto p = std::find_if(m_peers.begin(), m_peers.end(), [targetId](const Peer &i) {
            return i.id == targetId;
        });

        if (p == m_peers.end()) {
            qCritical() << "socket" << targetId << "is not found";
            return;
        }

        send(obj, p->socket);
    } else {
        send(obj, m_client);
    }
}

void IpcTransceiver::send(const QJsonObject &obj, QTcpSocket *socket) {
    Q_ASSERT(socket != nullptr);

    if (socket->state() != QTcpSocket::ConnectedState) {
        qCritical() << "socket is not connected, state=" << socket->state();
        return;
    }

    if (!socket->isWritable()) {
        qCritical() << "socket is not writeable";
        return;
    }

    socket->write(QJsonDocument(obj).toJson(QJsonDocument::Compact).append(PACKET_SEPERATOR));
    socket->flush();
}

bool IpcTransceiver::isClientConnected(IpcId id)
{
    auto p = std::find_if(m_peers.begin(), m_peers.end(), [id](const Peer &i) {
        return i.id == id;
    });

    return p != m_peers.end() && p->id != IpcId_Unknown;
}

IpcTransceiver::IpcId IpcTransceiver::lastSender() const
{
    return m_lastSender;
}

QJsonObject IpcTransceiver::header(int function)
{
    QJsonObject obj {};

    m_sendPacketId++;
    obj["packetId"] = m_sendPacketId;
    obj["sender_id"] = (int)m_id;
    obj["function"] = function;

    return obj;
}

void IpcTransceiver::onNewConnection()
{
    QTcpSocket *clientSocket = m_server->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &IpcTransceiver::onReadyRead);
    connect(clientSocket, &QTcpSocket::stateChanged, this, &IpcTransceiver::onSocketStateChanged);

    m_peers.push_back({IpcId_Unknown, clientSocket});
    // qDebug() << "new peer connected!";
}

void IpcTransceiver::onSocketStateChanged(QAbstractSocket::SocketState state)
{
    if (isServer()) {
        if (state == QAbstractSocket::UnconnectedState)
        {
            QTcpSocket *sender = static_cast<QTcpSocket*>(QObject::sender());

            auto p = std::find_if(m_peers.begin(), m_peers.end(), [sender](const Peer &i) {
                return i.socket == sender;
            });

            if (p != m_peers.end()) {
                m_peers.removeAll(*p);
                // qDebug() << "Peer " << p->id << "disconnected!";
                emit sigClientConnectionChanged(p->id, false);
            }
        }
    } else {
        if (state == QTcpSocket::UnconnectedState) {
            // qWarning("Server is disconnected!");
            m_reconnectTimer.start();
            emit sigServerConnectionChanged(false);
        }
        if (state == QTcpSocket::ConnectedState) {
            // qInfo("Server is connected!");
            m_reconnectTimer.stop();
            registerToServer();
            emit sigServerConnectionChanged(true);
        }
    }
}

void IpcTransceiver::onReadyRead()
{
    QTcpSocket *sender = static_cast<QTcpSocket*>(QObject::sender());

    // sometimes multiple packets arrive as 1 packet when server deploy too fast
    auto d = QString::fromLatin1(sender->readAll());
    auto packets = d.split(PACKET_SEPERATOR);

    // std::cout << d.toStdString() << "\n\n";

    for (auto &data : packets) {
        if (data.isEmpty()) continue;
        data = data.trimmed();

        data.remove(PACKET_SEPERATOR);
#if 0
        // drop header, for testing with Insomnia
        if (data.contains('{')) {
            data.remove(0, data.indexOf('{'));
        } else {
            return;
        }
#endif
        // qDebug() << data;

        QJsonParseError error;
        const auto doc = QJsonDocument::fromJson(data.toLatin1(), &error);

        if (error.error != QJsonParseError::NoError) {
            qCritical() << "Parse error:"<< error.errorString();
            std::cout << data.toStdString() << std::endl;
            continue;
        }

        // qDebug() << "OK";

        auto obj = doc.object();
        auto packetId = obj["packetId"].toInt();
        if (packetId == m_lastReceivePacketId) {
            // prevent packet duplication
            continue;
        }
        m_lastReceivePacketId = packetId;

        handleMessage(sender, doc.object());
    }
}

void IpcTransceiver::onReconnectTimer()
{
    Q_ASSERT(m_client != nullptr);

    m_client->connectToHost(QHostAddress(TCP_IP_ADDR), TCP_PORT);
    // qDebug() << "Re-connecting to server on port:" << TCP_PORT;
}
