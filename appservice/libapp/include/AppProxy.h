#ifndef APPPROXY_H_
#define APPPROXY_H_

class BaseReceiver;

#include "../interface/IApp.h"
#include "../interface/proxy/BaseAppMsgDef.h"
#include <ipc/ipctransceiver.h>

class AppProxy: public IApp
{
public:
    AppProxy(BaseReceiver* receiver=nullptr, const char* name=nullptr);
    virtual ~AppProxy();
public:
    static AppProxy* getInstance(BaseReceiver* receiver=nullptr, const char* name="appproxy");

    virtual void requestStartLogging(int requestID);
    virtual void requestStopLogging(int requestID);
    virtual void requestSetMemoryStrategy(int requestID, E_MEMORY_STRATEGY strategy);

    virtual void requestToRegisterApplication(const int& requestID, const APP_INFO_T& tAppInfo);
    virtual void requestToUnregisterApplication(const int& requestID, const char* strAppName);
    virtual void requestToRegisterApplicationLink(const int& requestID, const APP_LINK_VECTOR_T& vAppLink);

    virtual void requestToGoBack(const int& requestID);
    virtual void requestToGoApplication(const int& requestID, const char* strAppName, const char* strAppRole, const char* strIntent, const E_SHOW_OPT& eShowOpt=E_SHOW_OPT_CLEAR_AND_ADD);
    virtual void requestToGoApplication(const int& requestID, const char* strAppName, const char* strAppRole, const char* strIntent, const E_SHOW_OPT& eShowOpt, const E_HMI_APP_LAUNCH_TYPE& eType);
    virtual void requestToHideApplication(const int& requestID, const char* strAppName, const char* strAppRole);
    virtual void requestToHideApplication(const int& requestID, const char* strAppName, const char* strAppRole, const char* strIntent);
    virtual void requestToActivateApplication(const int& requestID, const char* strAppName, const bool& bActivation);

    // Entertainment Mute / Unmute
    virtual void requestActivateEntertainment(const int& requestID, const bool& isEntertainmentOn);

    // Change Window ID (AppRole To Window)
    virtual void requestUpdateDynamicWindow(const int& requestID, const char* strAppRole, const char* strNewWindowName);

    // The system popup enum components has used by the popup service.
    virtual void requestToShowSystemComponent(const int& requestID, const E_SYSTEM_COMPONENT& eSystemComponent, const char* strData=STRING_DATA_NONE);
    virtual void requestToHideSystemComponent(const int& requestID, const E_SYSTEM_COMPONENT& eSystemComponent, const char* strData=STRING_DATA_NONE);
    virtual void requestToSetVisibilityOfScreen(const int& requestID, const char* strScreenName, bool isVisible);
    virtual void requestChangeSidePanelPosition(const int& requestID, const bool& isLeftHandle);

    virtual void requestToPlayBeepSound(const int& requestID, const E_BEEP_SOUND_TYPE& eBeepSoundType);
    virtual void requestControlGUIComponent(const int& requestID, const E_GUI_COMPONENT& eGUIComponent, const E_GUI_CONTROL_COMMAND& eGUIControlCommand, const bool& bValue, const std::string& strValue);

    virtual void activeClusterNavigation(const E_NAVI_TYPE& eNaviType);

    virtual void requestToDestroyAppWindow(const int& requestID, const char* strAppRole);
    virtual void requestToCommunicateApplication(const int& requestID, const char* strSrc, const char* strDest, const char* strIntent);

    /* HMI application shall send an response message to the application service. */
    virtual void responseShowApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);                                   // void onCmdShowApplication(const int& requestID, const E_HMI_VIEW_ID& eViewID)
    virtual void responseHideApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);                                   // void onCmdHideApplication(const int& requestID)
    virtual void responseResumeApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);                                 // void onCmdResumeApplication(const int& requestID)
    virtual void responseGoBackResult(const int& requestID, const E_REQ_GO_BACK_RESULT& eResult);                                        // void onCmdGoBack(const int& requestID)
    virtual void responseSetVisibilityOfBackButtonResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);                         // void onCmdSetVisibilityOfBackButton(const int& requestID, const bool& isVisible)
    virtual void responseSetVisibilityOfHomeButtonResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);                         // void onCmdSetVisibilityOfHomeButton(const int& requestID, const bool& isVisible)
    virtual void responseShowTransitionAnimationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);                           // void onCmdShowTransitionAnimation(const int& requestID)
    virtual void responseCreateAppWindowResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void responseShowAppWindowResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void responseDestroyAppWindowResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void responseControlGUIComponentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);

    // Don't use below interface (Will be deprecated)
    virtual void requestToHideApplication(const int& requestID, const char* strAppName);
    virtual void requestToGoApplication(const int& requestID, const INTENT_T& tIntent);
    virtual void requestToGoApplication(const int& requestID, const char* strAppBinaryName, const char* strIntent=STRING_DATA_NONE);
    virtual void requestToGoApplication(const int& requestID, const char* strAppBinaryName, const E_SHOW_OPT& eShowOption, const char* strIntent);
    virtual void requestToGoApplication(const int& requestID, const char* strAppRole, const char* strIntent, const E_SHOW_OPT& eShowOption);
    virtual void requestToGoApplication(const int& requestID, const E_HMI_APP_ID& eAppID, const char* strIntent);
    virtual void requestToGoApplication(const int& requestID, const E_HMI_APP_ID& eAppID, const E_SHOW_OPT& eShowOption=E_SHOW_OPT_CLEAR_AND_ADD, const char* strIntent=STRING_DATA_NONE);
    virtual void requestToGoApplication(const int& requestID, const E_HMI_APP_ID& eAppID, const E_HMI_VIEW_ID& eViewID, const E_SHOW_OPT& eShowOption=E_SHOW_OPT_CLEAR_AND_ADD, const char* strIntent=STRING_DATA_NONE);
    virtual void requestToShowPopup(const int& requestID, const char* popupInfo);
    virtual void requestToHidePopup(const int& requestID);
    virtual void requestToShowKeyboard(const int& requestID, const char* keyboardInfo);
    virtual void requestToHideKeyboard(const int& requestID);
    virtual void onPopupActionResult(const int& requestID, const char* result);
    virtual void requestToGetAvailableScreen(const int& requestID);
    virtual void responseShowPopupResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void responseHidePopupResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void responseShowKeyboardResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void responseHideKeyboardResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void responseTerminateApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void requestToHideApplication(const int& requestID, const E_HMI_APP_ID& eAppID);
    virtual void requestToActivateApplication(const int& requestID, const E_HMI_APP_ID& eAppID, const bool& bActivation);
    virtual void requestPostMessage(const std::string& message);
    virtual void responseGetApplicationActivationResult(const int& requestID, const bool& bActivation, const E_REQ_RESULT_MSG& eResult);
    virtual void responseReadyToSuspendSystemResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void responseSuspendSystemResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void responseReadyToResumeSystemResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void responseResumeSystemResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void responseActivateApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);

private:
    IpcTransceiver *m_transceiver = IpcTransceiver::instance();
};

#endif //APPPROXY_H_
