#include "hmiapplication.h"

HMIApplication::HMIApplication()
{
    m_appManagerService = new AppManagerService();
}

void HMIApplication::initialize()
{
    sourceHMIDummyData();
    nonOverlayHMIDummyData();
    overlayHMIDummyData();
}

void HMIApplication::sourceHMIDummyData()
{
    // Home HMI, for example
    APP_INFO_T tAppInfo;
    tAppInfo.eAppId = E_HMI_APP_ID_HOME;
    strcpy(tAppInfo.strAppBinaryName,HMI_APP_NAME_HOME);
    strcpy(tAppInfo.strAppWindowName, WIN_NAME_HOME);
    strcpy(tAppInfo.strAppRole, HMI_ROLE_HOME);
    tAppInfo.appendWindowInfo(HMI_ROLE_HOME, WIN_NAME_HOME);      // AppRole1,WinName1
    tAppInfo.appendWindowInfo(HMI_ROLE_HOME_SETTING, WIN_NAME_HOME_EDIT_VIEW);     // AppRole2,WinName2
    tAppInfo.appendWindowInfo(HMI_ROLE_HOME_APPDRAWER, WIN_NAME_SIDE_PANEL_LEFT);
    tAppInfo.appendWindowInfo(HMI_ROLE_COMMON_CALL_BUBBLE, WIN_NAME_COMMON_CALL_BUBBLE);
    m_appManagerService->requestToRegisterApplication(0, tAppInfo);

    // TODO: For Home, Camera and User Hard Key
    // How to: http://vopengrok.lge.com:8122/search?full=requestToRegisterApplication&project=proteus_release
    // Copy & paste the current implementation of requestToRegisterApplication() from HMI code
}

void HMIApplication::nonOverlayHMIDummyData()
{
    // Radio HMI, for example
    APP_INFO_T tAppInfo;
    tAppInfo.eAppId = E_HMI_APP_ID_RADIO;
    strcpy(tAppInfo.strAppWindowName, WIN_NAME_RADIO);
    strcpy(tAppInfo.strAppBinaryName, HMI_APP_NAME_RADIO);
    strcpy(tAppInfo.strAppRole, HMI_ROLE_RADIO);
    tAppInfo.isApplicationActivation = false;
    tAppInfo.eAppType = E_HMI_APP_TYPE_ENTERTAINMENT;
    tAppInfo.appendWindowInfo(HMI_ROLE_RADIO, WIN_NAME_RADIO);
    tAppInfo.appendWindowInfo(HMI_ROLE_RADIO_AM, WIN_NAME_RADIO);
    tAppInfo.appendWindowInfo(HMI_ROLE_RADIO_FM, WIN_NAME_RADIO);
    tAppInfo.appendWindowInfo(HMI_ROLE_RADIO_DAB, WIN_NAME_RADIO);
    tAppInfo.appendWindowInfo(HMI_ROLE_RADIO_SPEECHMODE, WIN_NAME_RADIO_SPEECHMODE);
    m_appManagerService->requestToRegisterApplication(0, tAppInfo);

    // Register all the relationships based on requestToGoApplication() API logic
    APP_LINK_VECTOR_T tAppLink;
    tAppLink.vLinkData.push_back(APP_LINK_INFO_T(HMI_APP_NAME_SOURCESELECTOR, HMI_ROLE_SOURCESELECTOR, E_SHOW_OPT_ADD_OVERLAY));
    tAppLink.vLinkData.push_back(APP_LINK_INFO_T(HMI_APP_NAME_SPEECH, HMI_ROLE_SPEECH, E_SHOW_OPT_ADD_OVERLAY));
    m_appManagerService->requestToRegisterApplicationLink(E_HMI_APP_ID_RADIO, tAppLink);

    // TODO: For all non overlay HMI Application
    // How to: http://vopengrok.lge.com:8122/search?full=requestToRegisterApplication&project=proteus_release
    // Copy & paste the current implementation of requestToRegisterApplication() from HMI code
}

void HMIApplication::overlayHMIDummyData()
{
    // Settings HMI, for example
    APP_INFO_T tAppInfo;
    tAppInfo.eAppId = E_HMI_APP_ID_SETTINGS;
    strcpy(tAppInfo.strAppBinaryName, HMI_APP_NAME_SETTINGS);
    strcpy(tAppInfo.strAppWindowName, WIN_NAME_SETTING);
    strcpy(tAppInfo.strAppRole, HMI_ROLE_SETTINGS);
    tAppInfo.isApplicationActivation = false;
    tAppInfo.eAppType = E_HMI_APP_TYPE_NONE;
    tAppInfo.appendWindowInfo(HMI_ROLE_SETTINGS, WIN_NAME_SETTING);
    m_appManagerService->requestToRegisterApplication(E_HMI_APP_ID_SETTINGS, tAppInfo);

    // Register all the relationships based on requestToGoApplication() API logic
    APP_LINK_VECTOR_T tAppLink;
    tAppLink.vLinkData.push_back(APP_LINK_INFO_T(DOWNLOAD_MANAGER_APP_NAME, DOWNLOAD_MANAGER_APP_ROLE, E_SHOW_OPT_CLEAR_AND_ADD));
    tAppLink.vLinkData.push_back(APP_LINK_INFO_T(HMI_APP_NAME_SWUPGRADE, HMI_ROLE_SOTA, E_SHOW_OPT_ADD_OVERLAY));
    tAppLink.vLinkData.push_back(APP_LINK_INFO_T(HMI_APP_NAME_HOME, HMI_ROLE_HOME_SETTING, E_SHOW_OPT_ADD_OVERLAY));
    tAppLink.vLinkData.push_back(APP_LINK_INFO_T(HMI_APP_NAME_ALEXA, HMI_ROLE_ALEXA, E_SHOW_OPT_CLEAR_AND_ADD));
    tAppLink.vLinkData.push_back(APP_LINK_INFO_T(HMI_APP_NAME_TMALL, HMI_ROLE_TMALL, E_SHOW_OPT_CLEAR_AND_ADD));
    tAppLink.vLinkData.push_back(APP_LINK_INFO_T(HMI_APP_NAME_ACCOUNT, HMI_ROLE_ACCOUNT_PROFILE, E_SHOW_OPT_CLEAR_AND_ADD));
    tAppLink.vLinkData.push_back(APP_LINK_INFO_T(HMI_APP_NAME_PHONE, HMI_ROLE_PHONE, E_SHOW_OPT_CLEAR_AND_ADD));
    tAppLink.vLinkData.push_back(APP_LINK_INFO_T(HMI_APP_NAME_TEE, HMI_ROLE_DRIVER_ASSISTANCE, E_SHOW_OPT_CLEAR_AND_ADD));
    m_appManagerService->requestToRegisterApplicationLink(E_HMI_APP_ID_RADIO, tAppLink);

    // TODO: For all overlay HMI Application
    // How to: http://vopengrok.lge.com:8122/search?full=requestToRegisterApplication&project=proteus_release
    // Copy & paste the current implementation of requestToRegisterApplication() from HMI code
}
