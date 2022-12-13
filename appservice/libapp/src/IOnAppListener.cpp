#include "IOnAppListener.h"
#include <QDebug>
#include "../interface/proxy/BaseAppMsgDef.h"
#include <string.h>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

IOnAppListener::IOnAppListener()
{
    connect(m_tranceiver, &IpcTransceiver::sigHandleMessage, this, &IOnAppListener::onHandleMessages);
}

IOnAppListener::~IOnAppListener()
{
}

/*
void IOnAppListener::onGoBackResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void IOnAppListener::onGoApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void IOnAppListener::onRegisterApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void IOnAppListener::onUnregisterApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void IOnAppListener::onActivateApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void IOnAppListener::onShowSystemComponentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void IOnAppListener::onHideSystemComponentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void IOnAppListener::onSetVisibilityOfScreenResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void IOnAppListener::onCommunicateApplicationEvent(const int& requestID, const char* strSrc, const char* strDest, const char* strIntent)
{
}

void IOnAppListener::onShowPopupResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void IOnAppListener::onHidePopupResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void IOnAppListener::onShowKeyboardResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void IOnAppListener::onHideKeyboardResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void IOnAppListener::onSwitchEntertainmentAudioResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void IOnAppListener::onPlayBeepSoundResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void IOnAppListener::onHideApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void IOnAppListener::onGetAvailableScreenResult(const int& requestID, const SYSTEM_SCREEN_INFO_T& tData, const E_REQ_RESULT_MSG& eResult)
{
}

void IOnAppListener::onActivateAudioResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void IOnAppListener::onActivateEntertainmentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void IOnAppListener::onUpdateDynamicWindowResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void IOnAppListener::onCmdActivateApplication(const int& requestID, const bool& bActivation)
{
}

void IOnAppListener::onCmdGetApplicationActivation(const int& requestID)
{
}

void IOnAppListener::onCmdShowPopup(const int& requestID, const char* popupInfo)
{
}

void IOnAppListener::onCmdHidePopup(const int& requestID)
{
}

void IOnAppListener::onCmdShowKeyboard(const int& requestID, const char* keyboardInfo)
{
}

void IOnAppListener::onCmdHideKeyboard(const int& requestID)
{
}

void IOnAppListener::onCmdShowApplication(const int& requestID)
{
}

void IOnAppListener::onCmdShowApplication(const int& requestID, const char* strIntent)
{
}

void IOnAppListener::onCmdShowApplication(const int& requestID, const E_HMI_VIEW_ID& eViewID)
{
}

void IOnAppListener::onCmdShowApplication(const int& requestID, const E_HMI_VIEW_ID& eViewID, const char* strIntent)
{
}

void IOnAppListener::onCmdShowApplication(const int& requestID, const char* strAppRole, const char* strIntent)
{
}

void IOnAppListener::onCmdHideApplication(const int& requestID)
{
}

void IOnAppListener::onCmdHideApplication(const int& requestID, const char* strAppRole, const char* strIntent)
{
}

void IOnAppListener::onCmdResumeApplication(const int& requestID)
{
}

void IOnAppListener::onCmdResumeApplication(const int& requestID, const char* strIntent)
{
}

void IOnAppListener::onCmdResumeApplication(const int& requestID, const char* strAppRole, const char* strIntent)
{
}

void IOnAppListener::onCmdCreateAppWindow(const int& requestID, const char* strAppRole, const char* strIntent)
{
}

void IOnAppListener::onCmdShowAppWindow(const int& requestID, const char* strAppRole, const char* strIntent)
{
}

void IOnAppListener::onCmdDestroyAppWindow(const int& requestID, const char* strAppRole, const char* strIntent)
{
}

void IOnAppListener::onCmdTerminateApplication(const int& requestID)
{
}

void IOnAppListener::onCmdGoBack(const int& requestID)
{
}

void IOnAppListener::onCmdShowTransitionAnimation(const int& requestID, const char* strAppRole, const char* strIntent)
{
}

void IOnAppListener::onCmdReadyToSuspendSystem(const int& requestID)
{
}

void IOnAppListener::onCmdSuspendSystem(const int& requestID)
{
}

void IOnAppListener::onCmdReadyToResumeSystem(const int& requestID)
{
}

void IOnAppListener::onCmdResumeSystem(const int& requestID)
{
}

void IOnAppListener::onCmdSetVisibilityOfBackButton(const int& requestID, const bool& isVisible)
{
}

void IOnAppListener::onCmdSetVisibilityOfHomeButton(const int& requestID, const bool& isVisible)
{
}

void IOnAppListener::onPopupActionResult(const int& requestID, const char* result)
{
}

void IOnAppListener::onHMIApplicationForegroundStateChanged(E_HMI_APP_FOREGROUND_STATE eState)
{
}

void IOnAppListener::onHMIApplicationForegroundStateChanged(const char* strAppRole, E_HMI_APP_FOREGROUND_STATE eState)
{
}

void IOnAppListener::onSystemPopupVisibilityChanged(bool isVisibleSystemPopup)
{
}

void IOnAppListener::onSystemValetModeStatusChanged(bool isValetMode)
{
}

void IOnAppListener::onSystemLanguageChanged(const char* languageCode)
{
}

void IOnAppListener::onChangeSidePanelPositionResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{
}

void IOnAppListener::onShowSystemComponentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult, const std::string& reason)
{
}

void IOnAppListener::onHideSystemComponentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult, const std::string& reason)
{
}

void IOnAppListener::onPostMessage(const std::string& message)
{
}

void IOnAppListener::onControlGUIComponentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
{

}

void IOnAppListener::onCmdControlGUIComponent(const int& requestID, const E_GUI_COMPONENT& eGUIComponent, const E_GUI_CONTROL_COMMAND& eGUIControlCommand, const bool& bValue, const std::string& strValue)
{

}

void IOnAppListener::onNotifyClientConnected(const char* name, const char* path, const char* ver)
{

}

void IOnAppListener::onNotifyClientDisconnected(const char* name, const char* path)
{

}

void IOnAppListener::onNotifyApplicationStatus(const char* name, const E_HMI_APP_LAUNCH_STATE& eResult)
{

}

void IOnAppListener::onShowGoodbyeScreen(const bool& isVisible)
{

}
*/

bool IOnAppListener::onHandleMessages(const QJsonObject &obj)
{
    const auto function = obj.value("function").toInt();

    switch (function) {
    case E_APP_LISTENER_MSG_ONGOAPPLICATIONRESULT1: {
        const auto requestID = obj.value("requestID").toInt();
        const auto eResult = (E_REQ_RESULT_MSG)obj.value("eResult").toInt();

        onGoApplicationResult(requestID, eResult);
        break;
    }
    case E_APP_LISTENER_MSG_ONHIDEAPPLICATIONRESULT1: {
        const auto requestID = obj.value("requestID").toInt();
        const auto eResult = (E_REQ_RESULT_MSG)obj.value("eResult").toInt();

        onHideApplicationResult(requestID, eResult);
        break;
    }
    case E_APP_LISTENER_MSG_ONCMDSHOWAPPLICATION1: {
        const auto requestID = obj.value("requestID").toInt();
        const auto strAppRole = obj.value("strAppRole").toString();
        const auto strIntent = obj.value("strIntent").toString();

        onCmdShowApplication(requestID, cstr(strAppRole), cstr(strIntent));
        break;
    }
    case E_APP_LISTENER_MSG_ONCMDHIDEAPPLICATION2: {
        const auto requestID = obj.value("requestID").toInt();
        const auto strAppRole = obj.value("strAppRole").toString();

        onCmdHideApplication(requestID, cstr(strAppRole), "");
        break;
    }
    case E_APP_LISTENER_MSG_ONCMDGOBACK1: {
        const auto requestID = obj.value("requestID").toInt();
        onCmdGoBack(requestID);
        break;
    }
    case E_APP_LISTENER_MSG_ONBRFOREGROUNDAPPCHANGED1: {
        const auto appName = obj.value("appName").toString();
        const auto appRole = obj.value("appRole").toString();
        const auto isOverlay = obj.value("isOverlay").toBool();

        onBrForegroundAppChanged(cstr(appName), cstr(appRole), isOverlay);
        break;
    }
    case E_APP_LISTENER_MSG_ONBRAPPSTACKCHANGED1: {
        const auto arr = obj.value("appStack").toArray();
        // NOTE: deserialize
        QList<AppData> list {};
        for (const auto &i : arr) {
            list.append(AppData::deserialize(i.toObject()));
        }
        onBrAppStackChanged(list);
        break;
    }
    case E_APP_LISTENER_MSG_ONBRAPPGRAPHCHANGED1: {
        const auto o = obj.value("appGraph").toObject();
        onBrAppGraphChanged(Graph::deserialize(o));
        break;
    }
    case E_APP_LISTENER_MSG_ONBRMEMORYUSAGECHANGED1: {
        const auto usedStatic = obj.value("usedStatic").toDouble();
        const auto usedNonStatic = obj.value("usedNonStatic").toDouble();
        const auto total = obj.value("total").toDouble();
        onBrSystemMemoryChanged(usedStatic, usedNonStatic, total);
        break;
    }
    case E_APP_LISTENER_MSG_ONBRWINDOWLIFECHANGED1: {
        const auto strWindowName = obj.value("strWindowName").toString();
        const auto isCreated = obj.value("isCreated").toBool();
        std::vector<std::string> rolesThatUseWindow {};

        for (const auto &roles : obj.value("rolesThatUseWindow").toArray()) {
            rolesThatUseWindow.push_back(roles.toString().toStdString());
        }

        onBrWindowLifeStatusChanged(cstr(strWindowName), isCreated, rolesThatUseWindow);
        break;
    }
    case E_APP_LISTENER_MSG_ONBRTOTALKPICHANGED1: {
        const auto total = obj.value("total").toDouble();
        onBrTotalKpiChanged(total);
        break;
    }
    case E_APP_LISTENER_MSG_ONBRDESTROYTRIGGERED1: {
        const auto level = obj.value("level").toInt();
        onBrDestroyTriggered(level);
        break;
    }
    case E_APP_LISTENER_MSG_ONBRMEMORYLEVELCHANGED1: {
        const auto level = obj.value("level").toInt();
        onBrMemoryLevelChanged(level);
        break;
    }
    default: {
        return false;
    }
    }

    return true;
}
