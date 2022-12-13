#include "BaseAppDeploy.h"
#include "../proxy/BaseAppMsgDef.h"
// #include "base/log/LogUtil.h"
#include <string.h>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

// BaseAppDeploy::BaseAppDeploy(const int& nMsgSize)
    // // : BaseDeploy(nMsgSize)
// {
    // // registerObjPath(INTERFACE_APP_SERVICE_OBJECT);
    // // setThreadLock(this);
// }

// BaseAppDeploy::~BaseAppDeploy()
// {
// }

void BaseAppDeploy::onRegisterApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void BaseAppDeploy::onGoBackResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void BaseAppDeploy::onGoApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
    auto o = m_transceiver->header(E_APP_LISTENER_MSG_ONGOAPPLICATIONRESULT1);
    o["requestID"] = requestID;
    o["eResult"] = (int)eResult;
    // m_transceiver->broadcast(o);
    m_transceiver->send(o, IpcTransceiver::IpcId_Home);
}

void BaseAppDeploy::onHideApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
    auto o = m_transceiver->header(E_APP_LISTENER_MSG_ONHIDEAPPLICATIONRESULT1);
    o["requestID"] = requestID;
    o["eResult"] = (int)eResult;
    // m_transceiver->broadcast(o);
    m_transceiver->send(o, IpcTransceiver::IpcId_Home);
}

void BaseAppDeploy::onActivateApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void BaseAppDeploy::onShowSystemComponentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void BaseAppDeploy::onHideSystemComponentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void BaseAppDeploy::onShowSystemComponentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult, const std::string& reason)
{
}

void BaseAppDeploy::onHideSystemComponentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult, const std::string& reason)
{
}

void BaseAppDeploy::onSetVisibilityOfScreenResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void BaseAppDeploy::onCommunicateApplicationEvent(const int& requestID, const char* strSrc, const char* strDest, const char* strIntent)
{
}

void BaseAppDeploy::onShowPopupResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void BaseAppDeploy::onHidePopupResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void BaseAppDeploy::onShowKeyboardResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void BaseAppDeploy::onHideKeyboardResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void BaseAppDeploy::onSwitchEntertainmentAudioResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void BaseAppDeploy::onPlayBeepSoundResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void BaseAppDeploy::onGetAvailableScreenResult(const int& requestID, const SYSTEM_SCREEN_INFO_T& tData, const E_REQ_RESULT_MSG& eResult)
{
}

void BaseAppDeploy::onActivateAudioResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void BaseAppDeploy::onActivateEntertainmentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void BaseAppDeploy::onUpdateDynamicWindowResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void BaseAppDeploy::onChangeSidePanelPositionResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void BaseAppDeploy::onCmdActivateApplication(const int& requestID, const bool& bActivation)
{
}

void BaseAppDeploy::onCmdGetApplicationActivation(const int& requestID)
{
}

void BaseAppDeploy::onCmdShowApplication(const int& requestID, const char* strAppRole, const char* strIntent)
{
    auto o = m_transceiver->header(E_APP_LISTENER_MSG_ONCMDSHOWAPPLICATION1);
    o["requestID"] = requestID;
    o["strAppRole"] = strAppRole;
    o["strIntent"] = strIntent;
    // m_transceiver->broadcast(o);
    m_transceiver->send(o, IpcTransceiver::IpcId_Home);
}

void BaseAppDeploy::onCmdHideApplication(const int& requestID)
{
}

void BaseAppDeploy::onCmdHideApplication(const int& requestID, const char* strAppRole, const char* strIntent)
{
    auto o = m_transceiver->header(E_APP_LISTENER_MSG_ONCMDHIDEAPPLICATION2);
    o["requestID"] = requestID;
    o["strAppRole"] = strAppRole;
    o["strIntent"] = strIntent;
    // m_transceiver->broadcast(o);
    m_transceiver->send(o, IpcTransceiver::IpcId_Home);
}

void BaseAppDeploy::onCmdResumeApplication(const int& requestID)
{
}

void BaseAppDeploy::onCmdResumeApplication(const int& requestID, const char* strIntent)
{
}

void BaseAppDeploy::onCmdResumeApplication(const int& requestID, const char* strAppRole, const char* strIntent)
{
}

void BaseAppDeploy::onCmdCreateAppWindow(const int& requestID, const char* strAppRole, const char* strIntent)
{
}

void BaseAppDeploy::onCmdShowAppWindow(const int& requestID, const char* strAppRole, const char* strIntent)
{
}

void BaseAppDeploy::onCmdDestroyAppWindow(const int& requestID, const char* strAppRole, const char* strIntent)
{
    auto o = m_transceiver->header(E_APP_LISTENER_MSG_ONCMDDESTROYAPPWINDOW1);
    o["requestID"] = requestID;
    o["strAppRole"] = strAppRole;
    o["strIntent"] = strIntent;
    // m_transceiver->broadcast(o);
    m_transceiver->send(o, IpcTransceiver::IpcId_Home);
}

void BaseAppDeploy::onCmdTerminateApplication(const int& requestID)
{
}

void BaseAppDeploy::onCmdGoBack(const int& requestID)
{
    auto o = m_transceiver->header(E_APP_LISTENER_MSG_ONCMDGOBACK1);
    o["requestID"] = requestID;
    // m_transceiver->broadcast(o);
    m_transceiver->send(o, IpcTransceiver::IpcId_Home);
}

void BaseAppDeploy::onCmdShowTransitionAnimation(const int& requestID, const char* strAppRole, const char* strIntent)
{
}

void BaseAppDeploy::onCmdReadyToSuspendSystem(const int& requestID)
{
}

void BaseAppDeploy::onCmdSuspendSystem(const int& requestID)
{
}

void BaseAppDeploy::onCmdReadyToResumeSystem(const int& requestID)
{
}

void BaseAppDeploy::onCmdResumeSystem(const int& requestID)
{
}

void BaseAppDeploy::onCmdSetVisibilityOfBackButton(const int& requestID, const bool& isVisible)
{
}

void BaseAppDeploy::onCmdSetVisibilityOfHomeButton(const int& requestID, const bool& isVisible)
{
}

void BaseAppDeploy::onPopupActionResult(const int& requestID, const char* result)
{
}

void BaseAppDeploy::onHMIApplicationForegroundStateChanged(E_HMI_APP_FOREGROUND_STATE eState)
{

}

void BaseAppDeploy::onHMIApplicationForegroundStateChanged(const char *strAppRole, E_HMI_APP_FOREGROUND_STATE eState)
{

}

void BaseAppDeploy::onSystemPopupVisibilityChanged(bool isVisibleSystemPopup)
{
}

void BaseAppDeploy::onSystemValetModeStatusChanged(bool isValetMode)
{
}

void BaseAppDeploy::onSystemLanguageChanged(const char* languageCode)
{
}

void BaseAppDeploy::onUnregisterApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void BaseAppDeploy::onPostMessage(const std::string& reason)
{
}

void BaseAppDeploy::onCmdControlGUIComponent(const int& requestID, const E_GUI_COMPONENT& eGUIComponent, const E_GUI_CONTROL_COMMAND& eGUIControlCommand, const bool& bValue, const std::string& strValue)
{
}

void BaseAppDeploy::onControlGUIComponentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void BaseAppDeploy::onNotifyClientConnected(const char* name, const char* path, const char* ver)
{
}

void BaseAppDeploy::onNotifyClientDisconnected(const char* name, const char* path)
{
}

void BaseAppDeploy::onNotifyApplicationStatus(const char* name, const E_HMI_APP_LAUNCH_STATE& eResult)
{
}

void BaseAppDeploy::onShowGoodbyeScreen(const bool& isVisible)
{
}

void BaseAppDeploy::onBrForegroundApplicationChanged(const E_HMI_APP_ID &eAppID)
{

}

void BaseAppDeploy::onBrForegroundApplicationExtChanged(const char *strAppBinaryName)
{

}

void BaseAppDeploy::onBrForegroundApplicationRoleChanged(const char *strAppName, const char *strAppRole)
{
}

void BaseAppDeploy::onBrVideoInhibitStateChanged(const bool &isVideoInhibitState)
{

}

void BaseAppDeploy::onBrVehicleMovementStateChanged(const bool &isVehicleMoving)
{

}

void BaseAppDeploy::onBrForegroundAppChanged(const char *appName, const char *appRole, const bool &isOverlay)
{
    auto o = m_transceiver->header(E_APP_LISTENER_MSG_ONBRFOREGROUNDAPPCHANGED1);
    o["appName"] = appName;
    o["appRole"] = appRole;
    o["isOverlay"] = isOverlay;
    // m_transceiver->broadcast(o);
    m_transceiver->send(o, IpcTransceiver::IpcId_Home);
}

void BaseAppDeploy::onBrActiveClusterNaviChanged(const E_NAVI_TYPE &eNaviType)
{

}

void BaseAppDeploy::onBrAppStackChanged(const QList<AppData> &appStack)
{
    auto o = m_transceiver->header(E_APP_LISTENER_MSG_ONBRAPPSTACKCHANGED1);
    QJsonArray arr {};
    for (const AppData& i : appStack) {
        arr.append(i.serialize());
    }
    o["appStack"] = arr;
    // m_transceiver->broadcast(o);
    m_transceiver->send(o, IpcTransceiver::IpcId_Home);
}

void BaseAppDeploy::onBrAppGraphChanged(const Graph &graph)
{
    auto o = m_transceiver->header(E_APP_LISTENER_MSG_ONBRAPPGRAPHCHANGED1);

    o["appGraph"] = graph.serialize();
    // m_transceiver->broadcast(o);
    m_transceiver->send(o, IpcTransceiver::IpcId_Home);
}

void BaseAppDeploy::onBrSystemMemoryChanged(double usedStatic, double usedNonStatic, double total)
{
    auto o = m_transceiver->header(E_APP_LISTENER_MSG_ONBRMEMORYUSAGECHANGED1);

    o["usedStatic"] = usedStatic;
    o["usedNonStatic"] = usedNonStatic;
    o["total"] = total;

    // m_transceiver->broadcast(o);
    m_transceiver->send(o, IpcTransceiver::IpcId_Home);
}

void BaseAppDeploy::onBrWindowLifeStatusChanged(const char *strWindowName, bool isCreated, const std::vector<std::string> &rolesThatUseWindow)
{
    auto o = m_transceiver->header(E_APP_LISTENER_MSG_ONBRWINDOWLIFECHANGED1);

    QJsonArray arr {};
    for (const auto &role : rolesThatUseWindow) {
        arr.append(qstr(role));
    }

    o["strWindowName"] = strWindowName;
    o["isCreated"] = isCreated;
    o["rolesThatUseWindow"] = arr;

    // m_transceiver->broadcast(o);
    m_transceiver->send(o, IpcTransceiver::IpcId_Home);
}

void BaseAppDeploy::onBrTotalKpiChanged(double total)
{
    auto o = m_transceiver->header(E_APP_LISTENER_MSG_ONBRTOTALKPICHANGED1);

    o["total"] = total;

    // m_transceiver->broadcast(o);
    m_transceiver->send(o, IpcTransceiver::IpcId_Home);
}

void BaseAppDeploy::onBrDestroyTriggered(int level)
{
    auto o = m_transceiver->header(E_APP_LISTENER_MSG_ONBRDESTROYTRIGGERED1);

    o["level"] = level;
    // m_transceiver->broadcast(o);
    m_transceiver->send(o, IpcTransceiver::IpcId_Home);
}

void BaseAppDeploy::onBrMemoryLevelChanged(int level)
{
    auto o = m_transceiver->header(E_APP_LISTENER_MSG_ONBRMEMORYLEVELCHANGED1);

    o["level"] = level;
    // m_transceiver->broadcast(o);
    m_transceiver->send(o, IpcTransceiver::IpcId_Home);
}
