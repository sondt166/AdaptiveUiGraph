#ifndef BASEAPPDEPLOY_H_
#define BASEAPPDEPLOY_H_

#include "../IApp.h"
#include "graph.h"
#include "utils/singleton.h"
#include "ipc/ipctransceiver.h"

#include <QList>

class BaseAppDeploy: public IAppListener,
        public IAppBrListener
{
    MAKE_SINGLETON(BaseAppDeploy);
public:
    // BaseAppDeploy(const int& nMsgSize=0);
    // virtual ~BaseAppDeploy();
public:
    virtual void onRegisterApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void onUnregisterApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void onGoBackResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void onGoApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void onActivateApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void onShowSystemComponentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void onHideSystemComponentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void onShowSystemComponentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult, const std::string& reason);
    virtual void onHideSystemComponentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult, const std::string& reason);
    virtual void onSetVisibilityOfScreenResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void onCommunicateApplicationEvent(const int& requestID, const char* strSrc, const char* strDest, const char* strIntent);
    virtual void onShowPopupResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void onHidePopupResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void onShowKeyboardResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void onHideKeyboardResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void onSwitchEntertainmentAudioResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void onPlayBeepSoundResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void onHideApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void onGetAvailableScreenResult(const int& requestID, const SYSTEM_SCREEN_INFO_T& tData, const E_REQ_RESULT_MSG& eResult);
    virtual void onActivateAudioResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void onActivateEntertainmentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void onUpdateDynamicWindowResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void onChangeSidePanelPositionResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void onCmdActivateApplication(const int& requestID, const bool& bActivation);
    virtual void onCmdGetApplicationActivation(const int& requestID);    
    virtual void onCmdShowApplication(const int& requestID, const char* strAppRole, const char* strIntent);
    virtual void onCmdHideApplication(const int& requestID);
    virtual void onCmdHideApplication(const int& requestID, const char* strAppRole, const char* strIntent);
    virtual void onCmdResumeApplication(const int& requestID);
    virtual void onCmdResumeApplication(const int& requestID, const char* strIntent);
    virtual void onCmdResumeApplication(const int& requestID, const char* strAppRole, const char* strIntent);
    virtual void onCmdCreateAppWindow(const int& requestID, const char* strAppRole, const char* strIntent);
    virtual void onCmdShowAppWindow(const int& requestID, const char* strAppRole, const char* strIntent);
    virtual void onCmdDestroyAppWindow(const int& requestID, const char* strAppRole, const char* strIntent);
    virtual void onCmdTerminateApplication(const int& requestID);
    virtual void onCmdGoBack(const int& requestID);
    virtual void onCmdShowTransitionAnimation(const int& requestID, const char* strAppRole, const char* strIntent);
    virtual void onCmdReadyToSuspendSystem(const int& requestID);
    virtual void onCmdSuspendSystem(const int& requestID);
    virtual void onCmdReadyToResumeSystem(const int& requestID);
    virtual void onCmdResumeSystem(const int& requestID);
    virtual void onCmdSetVisibilityOfBackButton(const int& requestID, const bool& isVisible);
    virtual void onCmdSetVisibilityOfHomeButton(const int& requestID, const bool& isVisible);
    // virtual void onButtonEvent(const E_SWITCH& eSwitchType, const E_BUTTON& eButton, const E_ACTION& eAction);
    // virtual void onRotaryEvent(const E_ROTARY& eRotary, const E_ROTATION& eRotation, const int& step);
    virtual void onPopupActionResult(const int& requestID, const char* result);
    virtual void onHMIApplicationForegroundStateChanged(E_HMI_APP_FOREGROUND_STATE eState);
    virtual void onHMIApplicationForegroundStateChanged(const char* strAppRole, E_HMI_APP_FOREGROUND_STATE eState);
    virtual void onSystemPopupVisibilityChanged(bool isVisibleSystemPopup);
    virtual void onSystemValetModeStatusChanged(bool isValetMode);
    virtual void onSystemLanguageChanged(const char* languageCode);
    virtual void onPostMessage(const std::string& reason);
    // virtual void onFavouriteButtonEvent(const E_SWS_FAVOURITE_FUNCTION& eFavouriteFunction);
    virtual void onCmdControlGUIComponent(const int& requestID, const E_GUI_COMPONENT& eGUIComponent, const E_GUI_CONTROL_COMMAND& eGUIControlCommand, const bool& bValue, const std::string& strValue);
    virtual void onControlGUIComponentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void onNotifyClientConnected(const char* name, const char* path, const char* ver);
    virtual void onNotifyClientDisconnected(const char* name, const char* path);
    virtual void onNotifyApplicationStatus(const char* name, const E_HMI_APP_LAUNCH_STATE& eResult);
    virtual void onShowGoodbyeScreen(const bool& isVisible);

    // BrBaseAppDeploy.h clone
    virtual void onBrForegroundApplicationChanged(const E_HMI_APP_ID& eAppID);
    virtual void onBrForegroundApplicationExtChanged(const char* strAppBinaryName);
    virtual void onBrForegroundApplicationRoleChanged(const char* strAppName, const char* strAppRole);
    virtual void onBrVideoInhibitStateChanged(const bool& isVideoInhibitState);
    virtual void onBrVehicleMovementStateChanged(const bool& isVehicleMoving);
    virtual void onBrForegroundAppChanged(const char* appName, const char* appRole, const bool& isOverlay);
    virtual void onBrActiveClusterNaviChanged(const E_NAVI_TYPE& eNaviType);

    // son.mai added
    virtual void onBrAppStackChanged(const QList<AppData> &appStack);
    virtual void onBrAppGraphChanged(const Graph &graph);
    virtual void onBrSystemMemoryChanged(double usedStatic, double usedNonStatic, double total);
    virtual void onBrWindowLifeStatusChanged(const char *strWindowName, bool isCreated, const std::vector<std::string> &rolesThatUseWindow);
    virtual void onBrTotalKpiChanged(double total) override;
    virtual void onBrDestroyTriggered(int level) override;
    virtual void onBrMemoryLevelChanged(int level) override;

private:
    IpcTransceiver *m_transceiver = IpcTransceiver::instance();
};

#endif //BASEAPPDEPLOY_H_
