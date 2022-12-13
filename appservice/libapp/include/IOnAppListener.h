#ifndef ONAPPLISTENER_H_
#define ONAPPLISTENER_H_

#include "IApp.h"
#include "ipc/ipctransceiver.h"

#include <QObject>

class IOnAppListener: public QObject, public IAppListener, public IAppBrListener
{
    Q_OBJECT
public:
    IOnAppListener();
    virtual ~IOnAppListener();

public:
    /*
    // (Application Service -> Client) : Response                                                            // (Client -> Application Service) : Request virtual void onGoBackResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);                      // void requestToGoBack(const int& requestID)
    virtual void onGoApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);               // void requestToGoApplication(const int& requestID, const char* strAppBinaryName, const char* strAppRole, const char* strIntent, const E_SHOW_OPT& eShowOpt)
    virtual void onRegisterApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);         // void requestToRegisterApplication(const int& requestID, const APP_INFO_T& tAppInfo)
    virtual void onUnregisterApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);       // void requestToUnregisterApplication(const int& requestID, const char* strAppName)
    virtual void onActivateApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);         // void requestToActivateApplication(const int& requestID, const char* strAppBinaryName, const bool& bActivation)
    virtual void onShowSystemComponentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);         // void requestToShowSystemComponent(const int& requestID, const E_SYSTEM_COMPONENT& eSystemComponent, const char* strData)
    virtual void onHideSystemComponentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);         // void requestToHideSystemComponent(const int& requestID, const E_SYSTEM_COMPONENT& eSystemComponent, const char* strData)
    virtual void onShowSystemComponentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult, const std::string& reason);         // void requestToShowSystemComponent(const int& requestID, const E_SYSTEM_COMPONENT& eSystemComponent, const char* strData)
    virtual void onHideSystemComponentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult, const std::string& reason);         // void requestToHideSystemComponent(const int& requestID, const E_SYSTEM_COMPONENT& eSystemComponent, const char* strData)
    virtual void onSetVisibilityOfScreenResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);       // void requestToSetVisibilityOfScreen(const int& requestID, const char* strScreenName, bool isVisible)
    virtual void onCommunicateApplicationEvent(const int& requestID, const char* strSrc, const char* strDest, const char* strIntent); // void requestToCommunicateApplication(const int& requestID, std::string strSrc, std::string strDest, std::string strIntent)
    virtual void onHideApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);             // void requestToHideApplication(const int& requestID, const char* strAppBinaryName)
    virtual void onUpdateDynamicWindowResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);         // void requestUpdateDynamicWindow(const int& requestID, const char* strAppRole, const char* strNewWindowName)
    virtual void onChangeSidePanelPositionResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);     // void requestChangeSidePanelPosition(const int& requestID, const bool& isLeftHandle)
    virtual void onActivateEntertainmentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void onControlGUIComponentResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);

    // (Application Service -> Client) : Request                                                             // (Client -> Application Service) : Response
    virtual void onCmdActivateApplication(const int& requestID, const bool& bActivation);                    // void responseActivateApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
    virtual void onCmdGetApplicationActivation(const int& requestID);                                        // void responseGetApplicationActivationResult(const int& requestID, const bool& bActivation, const E_REQ_RESULT_MSG& eResult)
    virtual void onCmdShowApplication(const int& requestID, const char* strAppRole, const char* strIntent);  // void responseShowApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
    virtual void onCmdHideApplication(const int& requestID);                                                 // void responseHideApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
    virtual void onCmdHideApplication(const int& requestID, const char* strAppRole, const char* strIntent);
    virtual void onCmdResumeApplication(const int& requestID);                                               // void responseResumeApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
    virtual void onCmdResumeApplication(const int& requestID, const char* strIntent);
    virtual void onCmdResumeApplication(const int& requestID, const char* strAppRole, const char* strIntent);
    virtual void onCmdCreateAppWindow(const int& requestID, const char* strAppRole, const char* strIntent);
    virtual void onCmdShowAppWindow(const int& requestID, const char* strAppRole, const char* strIntent);
    virtual void onCmdDestroyAppWindow(const int& requestID, const char* strAppRole, const char* strIntent);
    virtual void onCmdControlGUIComponent(const int& requestID, const E_GUI_COMPONENT& eGUIComponent, const E_GUI_CONTROL_COMMAND& eGUIControlCommand, const bool& bValue, const std::string& strValue);
    virtual void onCmdTerminateApplication(const int& requestID);                                            // void responseTerminateApplicationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
    virtual void onCmdGoBack(const int& requestID);                                                          // void responseGoBackResult(const int& requestID, const E_REQ_GO_BACK_RESULT& eResult)
    virtual void onCmdShowTransitionAnimation(const int& requestID, const char* strAppRole, const char* strIntent);  // void responseShowTransitionAnimationResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
    virtual void onCmdReadyToSuspendSystem(const int& requestID);                                            // void responseReadyToSuspendSystemResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
    virtual void onCmdSuspendSystem(const int& requestID);                                                   // void responseSuspendSystemResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
    virtual void onCmdReadyToResumeSystem(const int& requestID);                                             // void responseReadyToResumeSystemResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
    virtual void onCmdResumeSystem(const int& requestID);                                                    // void responseResumeSystemResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)

    // This interface is provided for side panel application.
    virtual void onCmdSetVisibilityOfBackButton(const int& requestID, const bool& isVisible);                // void responseSetVisibilityOfBackButtonResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)
    virtual void onCmdSetVisibilityOfHomeButton(const int& requestID, const bool& isVisible);                // void responseSetVisibilityOfHomeButtonResult(const int& requestID, const E_REQ_RESULT_MSG& eResult)

    // (Application Service -> Client) : Notification
    // virtual void onButtonEvent(const E_SWITCH& eSwitchType, const E_BUTTON& eButton, const E_ACTION& eAction);
    // virtual void onRotaryEvent(const E_ROTARY& eRotary, const E_ROTATION& eRotation, const int& step);
    virtual void onHMIApplicationForegroundStateChanged(E_HMI_APP_FOREGROUND_STATE eState);
    virtual void onHMIApplicationForegroundStateChanged(const char* strAppRole, E_HMI_APP_FOREGROUND_STATE eState);
    virtual void onSystemPopupVisibilityChanged(bool isVisibleSystemPopup);
    virtual void onSystemValetModeStatusChanged(bool isValetMode);
    virtual void onSystemLanguageChanged(const char* languageCode);

    // Below feature is not ready
    virtual void onPlayBeepSoundResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void onGetAvailableScreenResult(const int& requestID, const SYSTEM_SCREEN_INFO_T& tData, const E_REQ_RESULT_MSG& eResult);

    // Please, Don't use below interfaces. (will be deleted.)
    virtual void onCmdShowApplication(const int& requestID);
    virtual void onCmdShowApplication(const int& requestID, const char* strIntent);
    virtual void onCmdShowApplication(const int& requestID, const E_HMI_VIEW_ID& eViewID);
    virtual void onCmdShowApplication(const int& requestID, const E_HMI_VIEW_ID& eViewID, const char* strIntent);
    virtual void onPopupActionResult(const int& requestID, const char* result);
    virtual void onShowPopupResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void onHidePopupResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void onShowKeyboardResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void onHideKeyboardResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void onSwitchEntertainmentAudioResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);
    virtual void onCmdShowPopup(const int& requestID, const char* popupInfo);
    virtual void onCmdHidePopup(const int& requestID);
    virtual void onCmdShowKeyboard(const int& requestID, const char* keyboardInfo);
    virtual void onCmdHideKeyboard(const int& requestID);
    virtual void onPostMessage(const std::string& message);
    virtual void onActivateAudioResult(const int& requestID, const E_REQ_RESULT_MSG& eResult);

    // virtual void onFavouriteButtonEvent(const E_SWS_FAVOURITE_FUNCTION& eFavouriteFunction);

    virtual void onNotifyClientConnected(const char* name, const char* path, const char* ver);
    virtual void onNotifyClientDisconnected(const char* name, const char* path);
    virtual void onNotifyApplicationStatus(const char* name, const E_HMI_APP_LAUNCH_STATE& eResult);

    virtual void onShowGoodbyeScreen(const bool& isVisible);
    */

public slots:
    virtual bool onHandleMessages(const QJsonObject &obj);

private:
    IpcTransceiver * m_tranceiver = IpcTransceiver::instance();
};

#endif //ONAPPLISTENER_H_
