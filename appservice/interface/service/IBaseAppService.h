#ifndef IBASEAPPSERVICE_H
#define IBASEAPPSERVICE_H

#include "../IApp.h"
// #include "base/interface/IBaseService.h"
#include <QJsonObject>
#include "ipc/ipctransceiver.h"

class IBaseAppService : public QObject,
                        public IApp
{
    Q_OBJECT
public:
    IBaseAppService();
    virtual ~IBaseAppService();

private slots:
    bool onHandleMessages(const QJsonObject &obj);

private:
    IpcTransceiver *transceiver;
};

#endif //IBASEAPPSERVICE_H
