#include "AppProxy.h"
// #include "base/log/LogUtil.h"

#include <QJsonArray>
#include <QJsonObject>

AppProxy::AppProxy(BaseReceiver* receiver, const char* name)
{
}

AppProxy::~AppProxy()
{
}

AppProxy* g_pAppProxy = nullptr;
AppProxy* AppProxy::getInstance(BaseReceiver* receiver, const char* name)
{
    if(g_pAppProxy != nullptr)
        return g_pAppProxy;

    g_pAppProxy = new AppProxy(receiver, name);

    return g_pAppProxy;
}

void AppProxy::requestStartLogging(int requestID)
{
    auto o = m_transceiver->header(E_APP_SERVICE_MSG_REQUESTSTARTLOGGING1);

    o["requestID"] = requestID;

    m_transceiver->send(o);
}

void AppProxy::requestStopLogging(int requestID)
{
    auto o = m_transceiver->header(E_APP_SERVICE_MSG_REQUESTSTOPLOGGING1);

    o["requestID"] = requestID;

    m_transceiver->send(o);
}

void AppProxy::requestSetMemoryStrategy(int requestID, E_MEMORY_STRATEGY strategy)
{
    auto o = m_transceiver->header(E_APP_SERVICE_MSG_REQUESTSETMEMORYSTRATEGY1);

    o["requestID"] = requestID;
    o["strategy"] = (int)strategy;

    m_transceiver->send(o);
}

void AppProxy::requestToRegisterApplication(const int& requestID, const APP_INFO_T& tAppInfo)
{
    auto o = m_transceiver->header(E_APP_SERVICE_MSG_REQUESTTOREGISTERAPPLICATION1);

    o["requestID"] = requestID;

    o["eAppId"] = (int)tAppInfo.eAppId;
    o["strAppBinaryName"] = tAppInfo.strAppBinaryName;
    o["strAppWindowName"] = tAppInfo.strAppWindowName;
    o["strAppRole"] = tAppInfo.strAppRole;
    o["strHMIRoleWindowPair"] = tAppInfo.strHMIRoleWindowPair;
    o["isApplicationActivation"] = tAppInfo.isApplicationActivation;
    o["eAppType"] = (int)tAppInfo.eAppType;

    m_transceiver->send(o);
}

void AppProxy::requestToUnregisterApplication(const int& requestID, const char* strAppName)
{
}

void AppProxy::requestToRegisterApplicationLink(const int &requestID, const APP_LINK_VECTOR_T &vAppLink)
{
    auto o = m_transceiver->header(E_APP_SERVICE_MSG_REQUESTTOREGISTERAPPLICATIONLINK1);

    QJsonArray arr {};

    for (const auto &i : vAppLink.vLinkData) {
        arr.append(i.serialize());
    }

    o["strAppBinaryName"] =qstr(vAppLink.strAppBinaryName);
    o["strAppRole"] =qstr(vAppLink.strAppRole);
    o["vLinkData"] = arr;
    m_transceiver->send(o);
}

void AppProxy::requestToGoBack(const int& requestID)
{
    auto o = m_transceiver->header(E_APP_SERVICE_MSG_REQUESTTOGOBACK1);

    o["requestID"] = requestID;

    m_transceiver->send(o);
}

void AppProxy::requestToGoApplication(const int& requestID, const char* strAppName, const char* strAppRole, const char* strIntent, const E_SHOW_OPT& eShowOpt)
{
    auto o = m_transceiver->header(E_APP_SERVICE_MSG_REQUESTTOGOAPPLICATION1);

    o["requestID"] = requestID;
    o["strAppName"] = strAppName;
    o["strAppRole"] = strAppRole;
    o["strIntent"] = strIntent;
    o["eShowOpt"] = (int)eShowOpt;

    m_transceiver->send(o);
}

void AppProxy::requestToGoApplication(const int& requestID, const char* strAppName, const char* strAppRole, const char* strIntent, const E_SHOW_OPT& eShowOpt, const E_HMI_APP_LAUNCH_TYPE& eType)
{
}

void AppProxy::requestToActivateApplication(const int& requestID, const char* strAppName, const bool& bActivation)
{
}

void AppProxy::requestToShowSystemComponent(const int& requestID, const E_SYSTEM_COMPONENT& eSystemComponent, const char* strData)
{
}

void AppProxy::requestToHideSystemComponent(const int& requestID, const E_SYSTEM_COMPONENT& eSystemComponent, const char* strData)
{
}

void AppProxy::requestToSetVisibilityOfScreen(const int& requestID, const char* strScreenName, bool isVisible)
{
}

void AppProxy::requestActivateEntertainment(const int& requestID, const bool& isEntertainmentOn)
{
}

void AppProxy::requestUpdateDynamicWindow(const int& requestID, const char* strAppRole, const char* strNewWindowName)
{
}

void AppProxy::requestToPlayBeepSound(const int& requestID, const E_BEEP_SOUND_TYPE& eBeepSoundType)
{
}

void AppProxy::requestToHideApplication(const int& requestID, const char* strAppName)
{
}

void AppProxy::requestToHideApplication(const int& requestID, const char* strAppName, const char* strAppRole)
{
    auto o = m_transceiver->header(E_APP_SERVICE_MSG_REQUESTTOHIDEAPPLICATION1);

    o["requestID"] = requestID;

    o["strAppName"] = strAppName;
    o["strAppRole"] = strAppRole;

    m_transceiver->send(o);
}

void AppProxy::requestToHideApplication(const int& requestID, const char* strAppName, const char* strAppRole, const char* strIntent)
{
    auto o = m_transceiver->header(E_APP_SERVICE_MSG_REQUESTTOHIDEAPPLICATION2);

    o["requestID"] = requestID;

    o["strAppName"] = strAppName;
    o["strAppRole"] = strAppRole;
    o["strIntent"] = strIntent;

    m_transceiver->send(o);
}

void AppProxy::requestToGetAvailableScreen(const int& requestID)
{
}

void AppProxy::activeClusterNavigation(const E_NAVI_TYPE& eNaviType)
{
}

void AppProxy::requestToDestroyAppWindow(const int& requestID, const char* strAppRole)
{
    auto o = m_transceiver->header(E_APP_SERVICE_MSG_REQUESTTODESTROYAPPWINDOW1);

    o["requestID"] = requestID;

    o["strAppRole"] = strAppRole;

    m_transceiver->send(o);
}

void AppProxy::requestToCommunicateApplication(const int& requestID, const char* strSrc, const char* strDest, const char* strIntent)
{
}

void AppProxy::responseActivateApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void AppProxy::responseGetApplicationActivationResult(const int& requestID, const bool& bActivation, const E_REQ_RESULT_MSG& eResult)
{
}

void AppProxy::responseShowApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void AppProxy::responseHideApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void AppProxy::responseResumeApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void AppProxy::responseReadyToSuspendSystemResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void AppProxy::responseSuspendSystemResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void AppProxy::responseReadyToResumeSystemResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void AppProxy::responseResumeSystemResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void AppProxy::responseGoBackResult(const int& requestID, const E_REQ_GO_BACK_RESULT& eResult)
{
}

void AppProxy::responseSetVisibilityOfBackButtonResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void AppProxy::responseSetVisibilityOfHomeButtonResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void AppProxy::responseShowTransitionAnimationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void AppProxy::responseCreateAppWindowResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void AppProxy::responseShowAppWindowResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void AppProxy::responseDestroyAppWindowResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void AppProxy::requestChangeSidePanelPosition(const int& requestID, const bool& isLeftHandle)
{
}

void AppProxy::requestPostMessage(const std::string& message)
{
}

void AppProxy::requestControlGUIComponent(const int& requestID, const E_GUI_COMPONENT& eGUIComponent, const E_GUI_CONTROL_COMMAND& eGUIControlCommand, const bool& bValue, const std::string& strValue)
{
}

void AppProxy::responseControlGUIComponentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

// Deprecated.
void AppProxy::requestToActivateApplication(const int& requestID, const E_HMI_APP_ID& eAppID, const bool& bActivation) {}
void AppProxy::requestToHideApplication(const int& requestID, const E_HMI_APP_ID& eAppID) {}
void AppProxy::requestToGoApplication(const int& requestID, const E_HMI_APP_ID& eAppID, const char* strIntent){}
void AppProxy::requestToGoApplication(const int& requestID, const E_HMI_APP_ID& eAppID, const E_SHOW_OPT& eShowOption, const char* strIntent) {}
void AppProxy::requestToGoApplication(const int& requestID, const E_HMI_APP_ID& eAppID, const E_HMI_VIEW_ID& eViewID, const E_SHOW_OPT& eShowOption, const char* strIntent) {}
void AppProxy::requestToGoApplication(const int& requestID, const INTENT_T& tIntent){}
void AppProxy::requestToGoApplication(const int& requestID, const char* strAppName, const char* strIntent) {}
void AppProxy::requestToGoApplication(const int& requestID, const char* strAppName, const E_SHOW_OPT& eShowOption, const char* strIntent) {}
void AppProxy::requestToGoApplication(const int& requestID, const char* strAppRole, const char* strIntent, const E_SHOW_OPT& eShowOpt) {}
void AppProxy::requestToShowPopup(const int& requestID, const char* popupInfo) {}
void AppProxy::requestToHidePopup(const int& requestID) {}
void AppProxy::requestToShowKeyboard(const int& requestID, const char* keyboardInfo) {}
void AppProxy::requestToHideKeyboard(const int& requestID) {}
void AppProxy::onPopupActionResult(const int& requestID, const char* result) {}
void AppProxy::responseShowPopupResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
void AppProxy::responseHidePopupResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
void AppProxy::responseShowKeyboardResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
void AppProxy::responseHideKeyboardResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
void AppProxy::responseTerminateApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
