#ifndef IAPP_INTERFACE_H
#define IAPP_INTERFACE_H

#include "AppMsgDef.h"
#include "graph.h"
// #include "userinput/UserinputMsgDef.h"
// #include "base/msg/MsgDef.h"
#include <string>
#include <QJsonArray>

#define MP_ATTACH_POINT_SYSTEM_APP "systemapp"

class IApp
{
public:
    virtual void requestStartLogging(int requestID) {}
    virtual void requestStopLogging(int requestID) {}
    virtual void requestSetMemoryStrategy(int requestID, E_MEMORY_STRATEGY strategy) {}
    /*****************************************************************************************
        Registration HMI Application
    *****************************************************************************************/
    virtual void requestToRegisterApplication(const int& requestID, const APP_INFO_T& tAppInfo) {}
    virtual void requestToUnregisterApplication(const int& requestID, const char* strAppName) {}
    virtual void requestToRegisterApplicationLink(const int& requestID, const APP_LINK_VECTOR_T& vAppLink) {}

    /*****************************************************************************************
        Transition HMI Applicatin (Foreground / Background)
    *****************************************************************************************/
    virtual void requestToGoBack(const int& requestID) {}
    virtual void requestToGoApplication(const int& requestID, const char* strAppBinaryName, const char* strAppRole, const char* strIntent, const E_SHOW_OPT& eShowOpt) {}
    virtual void requestToGoApplication(const int& requestID, const char* strAppName, const char* strAppRole, const char* strIntent, const E_SHOW_OPT& eShowOpt, const E_HMI_APP_LAUNCH_TYPE& eType) {}
    virtual void requestToHideApplication(const int& requestID, const char* strAppName) {}
    virtual void requestToHideApplication(const int& requestID, const char* strAppName, const char* strAppRole) {}
    virtual void requestToHideApplication(const int& requestID, const char* strAppName, const char* strAppRole, const char* strIntent) {}

    /*****************************************************************************************
        Activatin / Deactivation HMI Application
    *****************************************************************************************/
    virtual void requestToActivateApplication(const int& requestID, const char* strAppName, const bool& bActivation) {}
    virtual void requestActivateEntertainment(const int& requestID, const bool& isEntertainmentOn) {}
    virtual void requestUpdateDynamicWindow(const int& requestID, const char* strAppRole, const char* strNewWindowName) {}

    /*****************************************************************************************
        System Component Visibility (System Keyboard, System Popup, Side Panel)
    *****************************************************************************************/
    virtual void requestToShowSystemComponent(const int& requestID, const E_SYSTEM_COMPONENT& eSystemComponent, const char* strData) {}
    virtual void requestToHideSystemComponent(const int& requestID, const E_SYSTEM_COMPONENT& eSystemComponent, const char* strData) {}

    /*****************************************************************************************
        Additional Screen Visibility (Camera Screen, Map Screen, Video Screen)
    *****************************************************************************************/
    virtual void requestToSetVisibilityOfScreen(const int& requestID, const char* strScreenName, bool isVisible) {}
    virtual void requestChangeSidePanelPosition(const int& requestID, const bool& isLeftHandle) {}

    /* Beep Sound */
    virtual void requestToPlayBeepSound(const int& requestID, const E_BEEP_SOUND_TYPE& eBeepSoundType) {}
    virtual void requestToGetAvailableScreen(const int& requestID) {}

    virtual void activeClusterNavigation(const E_NAVI_TYPE& eNaviType) {}
    virtual void requestToDestroyAppWindow(const int& requestID, const char* strAppRole) {}
    virtual void requestToCommunicateApplication(const int& requestID, const char* strSrc, const char* strDest, const char* strIntent) {}

    // Response interface (The client shall send a response to AppService)
    virtual void responseActivateApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
    virtual void responseGetApplicationActivationResult(const int& requestID, const bool& bActivation, const E_REQ_RESULT_MSG& eResult) {}
    virtual void responseShowApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
    virtual void responseHideApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
    virtual void responseResumeApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
    virtual void responseTerminateApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
    virtual void responseCreateAppWindowResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
    virtual void responseShowAppWindowResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
    virtual void responseDestroyAppWindowResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
    virtual void responseReadyToSuspendSystemResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
    virtual void responseSuspendSystemResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
    virtual void responseReadyToResumeSystemResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
    virtual void responseResumeSystemResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
    virtual void responseGoBackResult(const int& requestID, const E_REQ_GO_BACK_RESULT& eResult) {}
    virtual void responseSetVisibilityOfBackButtonResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
    virtual void responseSetVisibilityOfHomeButtonResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
    virtual void responseControlGUIComponentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
    virtual void responseShowTransitionAnimationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}

    virtual void requestPostMessage(const std::string& message) {}
    virtual void requestControlGUIComponent(const int& requestID, const E_GUI_COMPONENT& eGUIComponent, const E_GUI_CONTROL_COMMAND& eGUIControlCommand, const bool& bValue, const std::string& strValue) {}
};

class IAppListener
{
public:
    virtual void onRegisterApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
    virtual void onUnregisterApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
    virtual void onGoBackResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
    virtual void onGoApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
    virtual void onActivateApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
    virtual void onShowSystemComponentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
    virtual void onShowSystemComponentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult, const std::string& reason) {}
    virtual void onHideSystemComponentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
    virtual void onHideSystemComponentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult, const std::string& reason) {}
    virtual void onSetVisibilityOfScreenResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
    virtual void onCommunicateApplicationEvent(const int& requestID, const char* strSrc, const char* strDest, const char* strIntent) {}
    virtual void onPlayBeepSoundResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
    virtual void onHideApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
    virtual void onGetAvailableScreenResult(const int& requestID, const SYSTEM_SCREEN_INFO_T& tData, const E_REQ_RESULT_MSG& eResult) {}
    virtual void onActivateAudioResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
    virtual void onActivateEntertainmentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
    virtual void onUpdateDynamicWindowResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
    virtual void onChangeSidePanelPositionResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
    virtual void onControlGUIComponentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult) {}
    virtual void onCmdActivateApplication(const int& requestID, const bool& bActivation) {}
    virtual void onCmdGetApplicationActivation(const int& requestID) {}
    virtual void onCmdShowApplication(const int& requestID, const char* strAppRole, const char* strIntent) {}
    virtual void onCmdHideApplication(const int& requestID, const char* strAppRole, const char* strIntent) {}
    virtual void onCmdCreateAppWindow(const int& requestID, const char* strAppRole, const char* strIntent) {}
    virtual void onCmdShowAppWindow(const int& requestID, const char* strAppRole, const char* strIntent) {}
    virtual void onCmdDestroyAppWindow(const int& requestID, const char* strAppRole, const char* strIntent) {}
    virtual void onCmdResumeApplication(const int& requestID, const char* strAppRole, const char* strIntent) {}
    virtual void onCmdTerminateApplication(const int& requestID) {}
    virtual void onCmdGoBack(const int& requestID) {}
    virtual void onCmdShowTransitionAnimation(const int& requestID, const char* strAppRole, const char* strIntent) {}
    virtual void onShowGoodbyeScreen(const bool& isVisible) {}

    /* Route event which is received from system service. (process lifecycle) */
    virtual void onCmdReadyToSuspendSystem(const int& requestID) {}
    virtual void onCmdSuspendSystem(const int& requestID) {}
    virtual void onCmdReadyToResumeSystem(const int& requestID) {}
    virtual void onCmdResumeSystem(const int& requestID) {}

    /* Left Sidepanel Back Button Visibility */
    virtual void onCmdSetVisibilityOfBackButton(const int& requestID, const bool& isVisible) {}
    virtual void onCmdControlGUIComponent(const int& requestID, const E_GUI_COMPONENT& eGUIComponent, const E_GUI_CONTROL_COMMAND& eGUIControlCommand, const bool& bValue, const std::string& strValue) {}

    /* Home button for valet mode */
    virtual void onCmdSetVisibilityOfHomeButton(const int& requestID, const bool& isVisible) {}

    /* Route event which is received from user input service. */
    // virtual void onButtonEvent(const E_SWITCH& eSwitchType, const E_BUTTON& eButton, const E_ACTION& eAction) {}
    // virtual void onFavouriteButtonEvent(const E_SWS_FAVOURITE_FUNCTION& eFavouriteFunction) {}
    // virtual void onRotaryEvent(const E_ROTARY& eRotary, const E_ROTATION& eRotation, const int& step) {}

    /* Broadcast Event */
    virtual void onHMIApplicationForegroundStateChanged(E_HMI_APP_FOREGROUND_STATE eState) {}
    virtual void onHMIApplicationForegroundStateChanged(const char* strAppRole, E_HMI_APP_FOREGROUND_STATE eState) {}
    virtual void onSystemPopupVisibilityChanged(bool isVisibleSystemPopup) {}
    virtual void onSystemValetModeStatusChanged(bool isValetMode) {}
    virtual void onSystemLanguageChanged(const char* languageCode) {}

    virtual void onPostMessage(const std::string& message) {}

    virtual void onNotifyClientConnected(const char* name, const char* path, const char* ver) {}
    virtual void onNotifyClientDisconnected(const char* name, const char* path) {}
    virtual void onNotifyApplicationStatus(const char* name, const E_HMI_APP_LAUNCH_STATE& eState) {}
};

class IAppBrListener
{
public:
    virtual void onBrForegroundApplicationChanged(const E_HMI_APP_ID& eAppID) {}
    virtual void onBrForegroundApplicationExtChanged(const char* strAppName) {}
    virtual void onBrForegroundApplicationRoleChanged(const char* strAppName, const char* strAppRole) {}
    virtual void onBrVideoInhibitStateChanged(const bool& isVideoInhibitState) {}
    virtual void onBrVehicleMovementStateChanged(const bool& isVehicleMoving) {}
    virtual void onBrForegroundAppChanged(const char* appName, const char* appRole, const bool& isOverlay) {}
    virtual void onBrActiveClusterNaviChanged(const E_NAVI_TYPE& eNaviType) {}
    virtual void onBrAppStackChanged(const QList<AppData> &appStack) {}
    virtual void onBrAppGraphChanged(const Graph &graph) {}
    virtual void onBrSystemMemoryChanged(double usedStatic, double usedNonStatic, double total) {}
    virtual void onBrTotalKpiChanged(double total) {}
    virtual void onBrDestroyTriggered(int level) {}
    virtual void onBrMemoryLevelChanged(int level) {}
    [[deprecated]] virtual void onBrWindowLifeStatusChanged(const char *strWindowName, bool isCreated, const std::vector<std::string> &rolesThatUseWindow) {}
};

#endif //IAPP_INTERFACE_H
