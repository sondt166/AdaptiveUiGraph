#include "IBaseAppService.h"
#include "../proxy/BaseAppMsgDef.h"
// #include "base/log/LogUtil.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

IBaseAppService::IBaseAppService()
    : QObject(nullptr),
      transceiver(IpcTransceiver::instance())
{
    connect(transceiver, &IpcTransceiver::sigHandleMessage, this, &IBaseAppService::onHandleMessages);
}

IBaseAppService::~IBaseAppService()
{
}

bool IBaseAppService::onHandleMessages(const QJsonObject &obj)
{
    const auto function = obj.value("function").toInt();

    switch (function) {
    case E_APP_SERVICE_MSG_REQUESTTOREGISTERAPPLICATION1: {
        const int requestID = obj.value("requestID").toInt();
        APP_INFO_T tAppInfo {};

        tAppInfo.eAppId = (E_HMI_APP_ID)obj.value("eAppId").toInt();

        qstr2carray(obj.value("strAppBinaryName").toString(), tAppInfo.strAppBinaryName);
        qstr2carray(obj.value("strAppWindowName").toString(), tAppInfo.strAppWindowName);
        qstr2carray(obj.value("strAppRole").toString(), tAppInfo.strAppRole);
        qstr2carray(obj.value("strHMIRoleWindowPair").toString(), tAppInfo.strHMIRoleWindowPair);

        tAppInfo.isApplicationActivation = obj.value("isApplicationActivation").toInt();
        tAppInfo.eAppType = (E_HMI_APP_TYPE)obj.value("eAppType").toInt();

        requestToRegisterApplication(requestID, tAppInfo);
        break;
    }
    case E_APP_SERVICE_MSG_REQUESTTOREGISTERAPPLICATIONLINK1: {
        const int requestID = obj.value("requestID").toInt();

        APP_LINK_VECTOR_T list {};

        list.strAppBinaryName = obj.value("strAppBinaryName").toString().toStdString();
        list.strAppRole = obj.value("strAppRole").toString().toStdString();

        for (const auto &i : obj.value("vLinkData").toArray()) {
            list.vLinkData.push_back(APP_LINK_INFO_T::deserialize(i.toObject()));
        }

        requestToRegisterApplicationLink(requestID, list);
        break;
    }
    case E_APP_SERVICE_MSG_REQUESTTOGOBACK1: {
        const auto requestID = obj.value("requestID").toInt();
        requestToGoBack(requestID);
        break;
    }
    case E_APP_SERVICE_MSG_REQUESTTOGOAPPLICATION1: {
        const auto requestID = obj.value("requestID").toInt();
        const auto strAppBinaryName = obj.value("strAppName").toString();
        const auto strAppRole = obj.value("strAppRole").toString();
        const auto strIntent = obj.value("strIntent").toString();
        const auto eShowOpt = (E_SHOW_OPT)obj.value("eShowOpt").toInt();
        requestToGoApplication(requestID,
                               cstr(strAppBinaryName),
                               cstr(strAppRole),
                               cstr(strIntent),
                               eShowOpt);
        break;
    }

    case E_APP_SERVICE_MSG_REQUESTTOHIDEAPPLICATION1: {
        const int requestID = obj.value("requestID").toInt();
        const auto strAppName = obj.value("strAppName").toString();
        const auto strAppRole = obj.value("strAppRole").toString();
        requestToHideApplication(requestID, cstr(strAppName), cstr(strAppRole));
        break;
    }
    case E_APP_SERVICE_MSG_REQUESTTOHIDEAPPLICATION2: {
        const int requestID = obj.value("requestID").toInt();
        const auto strAppName = obj.value("strAppName").toString();
        const auto strAppRole = obj.value("strAppRole").toString();
        const auto strIntent = obj.value("strIntent").toString();
        requestToHideApplication(requestID,
                                 cstr(strAppName),
                                 cstr(strAppRole),
                                 cstr(strIntent));
        break;
    }
    case E_APP_SERVICE_MSG_REQUESTTODESTROYAPPWINDOW1: {
        const int requestID = obj.value("requestID").toInt();
        const auto strAppRole = obj.value("strAppRole").toString();
        requestToDestroyAppWindow(requestID, cstr(strAppRole));
        break;
    }
    case E_APP_SERVICE_MSG_REQUESTSTARTLOGGING1: {
        const int requestID = obj.value("requestID").toInt();
        requestStartLogging(requestID);
        break;
    }
    case E_APP_SERVICE_MSG_REQUESTSTOPLOGGING1: {
        const int requestID = obj.value("requestID").toInt();
        requestStopLogging(requestID);
        break;
    }
    case E_APP_SERVICE_MSG_REQUESTSETMEMORYSTRATEGY1: {
        const int requestID = obj.value("requestID").toInt();
        const E_MEMORY_STRATEGY strategy = (E_MEMORY_STRATEGY)obj.value("strategy").toInt();
        requestSetMemoryStrategy(requestID, strategy);
        break;
    }
    default: {
        // qWarning("Not implemented");
        return false;
    }
    }

    return true;
}

