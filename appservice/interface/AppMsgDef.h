#ifndef APPMSGDEF_H
#define APPMSGDEF_H

#include "list"
#include "string"
#include "string.h"
#include "vector"
#define STRING_DATA_NONE ""

#include "utils/stringhelper.h"

#include <QJsonObject>

enum E_MEMORY_STRATEGY {
    E_STRATEGY_NONE,
    E_STRATEGY_HOME,   // destroy window when go to Home
    E_STRATEGY_GRAPH   // destory window with graph method
};

enum E_HMI_APP_ID
{
    E_HMI_APP_ID_INVALID = -1,
    E_HMI_APP_ID_HOME = 0,
    E_HMI_APP_ID_RADIO_AM,         // deprecated
    E_HMI_APP_ID_RADIO_FM,         // deprecated
    E_HMI_APP_ID_RADIO_DAB,        // deprecated
    E_HMI_APP_ID_RADIO,
    E_HMI_APP_ID_RADIO_SXM360L,
    E_HMI_APP_ID_MEDIA,
    E_HMI_APP_ID_SETTING_AUDIO,    // deprecated
    E_HMI_APP_ID_SETTING_BT,       // deprecated
    E_HMI_APP_ID_SIDE_PANEL,
    E_HMI_APP_ID_SIDE_STEPS,
    E_HMI_APP_ID_TOW_BAR,
    E_HMI_APP_ID_POPUP,            // deprecated
    E_HMI_APP_ID_PHONE,
    E_HMI_APP_ID_ENG_SCREEN,
    E_HMI_APP_ID_ECO,
    E_HMI_APP_ID_SPEECH,           // deprecated
    E_HMI_APP_ID_CLIMATE,
    E_HMI_APP_ID_SEAT,
    E_HMI_APP_ID_DYNAMICI,
    E_HMI_APP_ID_LIGHTING,
    E_HMI_APP_ID_DRV4X4I,
    E_HMI_APP_ID_PHONE_PROJECTION,
    E_HMI_APP_ID_LTL,
    E_HMI_APP_ID_DIMENSION,
    E_HMI_APP_ID_ASI,
    E_HMI_APP_ID_LFL,
    E_HMI_APP_ID_DEPICP,
    E_HMI_APP_ID_EV,
    E_HMI_APP_ID_SETTINGS,
    E_HMI_APP_ID_KEYBOARD,
    E_HMI_APP_ID_SOURCE_SELECTOR,
    E_HMI_APP_ID_SYSTEM_POPUP,
    E_HMI_APP_ID_NAVIGATION,
    E_HMI_APP_ID_SOTA,
    E_HMI_APP_ID_PARKING,
    E_HMI_APP_ID_CAMERA,
    E_HMI_APP_ID_ONLINE_MEDIA,
    E_HMI_APP_ID_DCM,
    E_HMI_APP_ID_DCR,
    E_HMI_APP_ID_VALET_MODE,
    E_HMI_APP_ID_NOTIFICATION,
    E_HMI_APP_ID_SPEECHPTT,
    E_HMI_APP_ID_SMARTSETTINGS,
    E_HMI_APP_ID_DISCLAIMER,
    E_HMI_APP_ID_VOICEPURE,     // changed speech to voicepure
    E_HMI_APP_ID_DEPARTURE,
    E_HMI_APP_ID_SETTING_CCF,
    E_HMI_APP_ID_TJP,
    E_HMI_APP_ID_TOW_ASSIST,
    E_HMI_APP_ID_GREETINGS,
    E_HMI_APP_ID_LOWERSCREENBLADE,
    E_HMI_APP_ID_STARTUP_WIZARD,
    E_HMI_APP_ID_SUPER_ICP,
    E_HMI_APP_ID_ACCOUNT,
    E_HMI_APP_ID_CONNECTED_MSG,
    E_HMI_APP_ID_SOURCE_PICKER,
    E_HMI_APP_ID_LOADING_WEBAPP,
    E_HMI_APP_ID_VEHICLE_CONTROL,
    E_HMI_APP_ID_ALEXA,
    E_HMI_APP_ID_SHOWROOM,
    E_HMI_APP_ID_TEE,
    E_HMI_APP_ID_TMALL,
    E_HMI_APP_ID_NUM
};

enum E_REQ_RESULT_MSG
{
    E_REQ_RESULT_MSG_INVALID = -1,
    E_REQ_RESULT_MSG_FAILED = 0,
    E_REQ_RESULT_MSG_OK,
    E_REQ_RESULT_MSG_NUM
};

enum E_REQ_GO_BACK_RESULT
{
    E_REQ_GO_BACK_RESULT_INVALID = -1,
    E_REQ_GO_BACK_RESULT_DEPTH_BACK_OK = 0,
    E_REQ_GO_BACK_RESULT_NEEDED_GO_PREVIOUS_APP,
    E_REQ_GO_BACK_RESULT_NUM
};

enum E_HMI_APP_FOREGROUND_STATE
{
    E_HMI_APP_FOREGROUND_STATE_INVALID = -1,
    E_HMI_APP_FOREGROUND_STATE_BACKGROUND = 0,
    E_HMI_APP_FOREGROUND_STATE_FOREGROUND
};

enum E_HMI_APP_LAUNCH_STATE
{
    E_HMI_APP_LAUNCH_START = 0,
    E_HMI_APP_LAUNCH_END,
    E_HMI_APP_LAUNCH_FAIL,
    E_HMI_APP_LAUNCH_STOP
};

enum E_NAVI_TYPE
{
    E_NAVI_NONE = 0,
    E_NAVI_NATIVE,
    E_NAVI_PROJECTION
};

enum E_HMI_APP_TYPE
{
    E_HMI_APP_TYPE_INVALID = -1,
    E_HMI_APP_TYPE_NONE,
    E_HMI_APP_TYPE_ENTERTAINMENT,
    E_HMI_APP_TYPE_NON_ENTERTAINMENT,
    E_HMI_APP_TYPE_OVERLAY
};

enum E_SHOW_OPT{
    E_SHOW_OPT_INVALID = -1,
    E_SHOW_OPT_ADD = 0,          // Default option : Added HMI app into history stack.
    E_SHOW_OPT_ADD_OVERLAY,      // Overlay option : Added HMI app as overlay app into history stack, but previous app maintains foreground state.
    E_SHOW_OPT_CLEAR_AND_ADD,    // Clear history stack and added HMI app into history stack.
    E_SHOW_OPT_CLEAR_DUPLICATE_AND_ADD, // If the same application(and same role) exist in the stack, it is removed and Added HMI app into history stack.
    E_SHOW_OPT_NUM
};

enum E_HMI_APP_LAUNCH_TYPE
{
    E_HMI_APP_LAUNCH_TYPE_INVALID = -1,
    E_HMI_APP_LAUNCH_TYPE_FAVORITEKEY = 0,
    E_HMI_APP_LAUNCH_TYPE_NOT_DEFINED,
    E_HMI_APP_LAUNCH_TYPE_NUM
};

enum E_SYSTEM_COMPONENT{
    E_SYSTEM_COMPONENT_INVALID = -1,
    E_SYSTEM_COMPONENT_SIDEPANEL_LEFT = 0,
    E_SYSTEM_COMPONENT_SIDEPANEL_RIGHT,
    E_SYSTEM_COMPONENT_SIDEPANEL_BOTH_LEFT_AND_RIGHT,
    E_SYSTEM_COMPONENT_SIDEPANEL_VIEW,
    E_SYSTEM_COMPONENT_SIDEPANEL_BACKBUTTON,
    E_SYSTEM_COMPONENT_SIDEPANEL_HOMEBUTTON,
    E_SYSTEM_COMPONENT_SYSTEM_KEYBOARD,
    E_SYSTEM_COMPONENT_SYSTEM_ALERTS,
    E_SYSTEM_COMPONENT_SYSTEM_POPUP,
    E_SYSTEM_COMPONENT_SYSTEM_POPUP_ANY_SCREEN,
    E_SYSTEM_COMPONENT_ALEXA_VOICE_CHROME,
    E_SYSTEM_COMPONENT_SPEECHMODE,
    E_SYSTEM_COMPONENT_TMALL_VOICE_CHROME,
    E_SYSTEM_COMPONENT_ALEXA_VISUAL_FEEDBACK,
    E_SYSTEM_COMPONENT_TMALL_VISUAL_FEEDBACK,
    E_SYSTEM_COMPONENT_NUM
};

enum E_GUI_COMPONENT{
    E_GUI_COMPONENT_INVALID = -1,
    E_GUI_COMPONENT_SIDEPANEL_BACKBUTTON = 0,
    E_GUI_COMPONENT_SIDEPANEL_HOMEBUTTON,
    E_GUI_COMPONENT_NUM
};

enum E_GUI_CONTROL_COMMAND{
    E_GUI_CONTROL_COMMAND_INVALID = -1,
    E_GUI_CONTROL_COMMAND_SET_VISIBILITY = 0,
    E_GUI_CONTROL_COMMAND_SET_DIMMING,
    E_GUI_CONTROL_COMMAND_NUM
};

struct APP_INFO_T {
    E_HMI_APP_ID eAppId;
    char strAppBinaryName[100];
    char strAppWindowName[100]; // Parent Window Name (Group Window Name)
    char strAppRole[100];       // Will be deplecated
    char strHMIRoleWindowPair[700]; // Example) "AppRole1,AppWindowName1:AppRole2,AppWindowName2" (Support Multi-Window by AppRole)
    bool isApplicationActivation;
    E_HMI_APP_TYPE eAppType;

    APP_INFO_T()
        : eAppId(E_HMI_APP_ID_INVALID)
        , isApplicationActivation(true)
        , eAppType(E_HMI_APP_TYPE_NONE)
    {
        memset(strAppBinaryName, 0x00, sizeof(strAppBinaryName));
        memset(strAppWindowName, 0x00, sizeof(strAppWindowName));
        memset(strAppRole,       0x00, sizeof(strAppRole));
        memset(strHMIRoleWindowPair, 0x00, sizeof(strHMIRoleWindowPair));
    }

    inline void appendWindowInfo(const char* appRole, const char* windowName)
    {
        std::string origin(strHMIRoleWindowPair);
        std::string target(appRole);
        target = target.append(",");
        target = target.append(windowName);
        if (false != origin.empty())
        {
            origin = origin.append(target);
        }
        else
        {
            if ((origin.size()+(target.size()+1)) <= (sizeof(strHMIRoleWindowPair)))
            {
                origin = origin.append(":");
                origin = origin.append(target);
            }
            else
            {
                // No Action
            }
        }

        strncpy(strHMIRoleWindowPair, origin.c_str(), origin.size());
    }
};

struct APP_LINK_INFO_T {
    QString strAppBinaryName;
    QString strAppRole;
    E_SHOW_OPT eShowOption;

    APP_LINK_INFO_T()
        : strAppBinaryName("")
        , strAppRole("")
        , eShowOption(E_SHOW_OPT_INVALID)
    {
    }

    APP_LINK_INFO_T(const QString &appName, const QString &appRole, E_SHOW_OPT showOpt)
        : strAppBinaryName(appName), strAppRole(appRole), eShowOption(showOpt)
    {
    }

    QJsonObject serialize() const {
        QJsonObject o {};
        o["appName"] = strAppBinaryName;
        o["appRole"] = strAppRole;
        o["showOption"] = (int)eShowOption;
        return o;
    }

    static APP_LINK_INFO_T deserialize(const QJsonObject &o) {
        APP_LINK_INFO_T result;
        result.strAppBinaryName = o["appName"].toString();
        result.strAppRole = o["appRole"].toString();
        result.eShowOption = (E_SHOW_OPT)o["showOption"].toInt();
        return result;
    }
};

struct APP_LINK_VECTOR_T {
    std::string strAppBinaryName;
    std::string strAppRole;
    std::vector<APP_LINK_INFO_T> vLinkData;
};

enum E_BEEP_SOUND_TYPE{
    E_BEEP_SOUND_TYPE_INVALID = -1,
    E_BEEP_SOUND_TYPE_SINGLE_KEY,
    E_BEEP_SOUND_TYPE_DOUBLE_KEY,
    E_BEEP_SOUND_TYPE_SINGLE_TOUCH,
    E_BEEP_SOUND_TYPE_DOUBLE_TOUCH,
    E_BEEP_SOUND_TYPE_NUM
};

// Unused Type (To be deleted.)
typedef int INTENT_T;
typedef int SYSTEM_SCREEN_INFO_T;
typedef int E_HMI_VIEW_ID;
#define E_HMI_VIEW_ID_INVALID                               0
#define E_HMI_VIEW_ID_HOME_MAIN                             E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_NAVIGATION_MAIN                       E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_RADIO_MAIN                            E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_RADIO_AM                              E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_RADIO_FM                              E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_RADIO_DAB                             E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_RADIO_DRM                             E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_RADIO_SXM_SAT                         E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_RADIO_SXM_IP                          E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_RADIO_CONNECTEDRADIO_IP               E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_RADIO_ISDBT                           E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_RADIO_FM_NEWS                         E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_RADIO_FM_TA                           E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_RADIO_FM_ALARM                        E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_RADIO_DAB_ANNOUNCEMENT                E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_MEDIA_MAIN                            E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_MEDIA_PLAYBACK_USB0                   E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_MEDIA_PLAYBACK_USB1                   E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_MEDIA_PLAYBACK_USB2                   E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_MEDIA_PLAYBACK_USB3                   E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_MEDIA_PLAYBACK_USB4                   E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_MEDIA_PLAYBACK_USB5                   E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_MEDIA_PLAYBACK_USB6                   E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_MEDIA_PLAYBACK_USB7                   E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_MEDIA_PLAYBACK_STREAMING_SPOTIFY      E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_MEDIA_PLAYBACK_STREAMING_AUDIBLE      E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_MEDIA_PLAYBACK_STREAMING_TUNEIN       E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_MEDIA_PLAYBACK_STREAMING_DEEZER       E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_SETTING_NAVIGATION                    E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_SETTING_AUDIO                         E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_SETTING_DISPLAY                       E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_SETTING_BT                            E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_SETTING_SEAT                          E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_SIDE_STEPS_MAIN                       E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_TOW_BAR_MAIN                          E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_SXM360L_MAIN                          E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_PHONE_MAIN                            E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_PHONE_BT_A2DP                         E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_PHONE_TTS_EMAIL                       E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_PHONE_TTS_SMS                         E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_CLIMATE_MAIN                          E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_ENGSCR_MAIN                           E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_ECO_MAIN                              E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_SPEECH_MAIN                           E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_SEAT_MAIN                             E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_DYNAMICI_MAIN                         E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_LIGHTING_MAIN                         E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_DRV4X4I_MAIN                          E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_PHONE_PROJECTION_MAIN                 E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_PHONE_PROJECTION_CARPLAY_MEDIA        E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_PHONE_PROJECTION_ANDROID_AUTO_MEDIA   E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_LTL_MAIN                              E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_DIMENSION_MAIN                        E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_ASI_MAIN                              E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_LFL_MAIN                              E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_DEPICP_MAIN                           E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_EV_MAIN                               E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_SOURCE_SELECTOR_MAIN                  E_HMI_VIEW_ID_INVALID
#define E_HMI_VIEW_ID_NUM                                   E_HMI_VIEW_ID_INVALID

#include <QString>
#include <QMetaType>
class AppData
{
public:
    AppData() : m_empty(true), m_name(), m_role(), m_windowName(), m_showOption() {}

    AppData(const QString &_name, const QString &_role,
                 const QString &_windowName, E_SHOW_OPT _opt)
        : m_empty(_name.isEmpty() || _role.isEmpty()),
          m_name(_name), m_role(_role),
          m_windowName(_windowName), m_showOption(_opt) {}

    AppData(const AppData &_rhs)
        : m_empty(_rhs.m_empty), m_name(_rhs.m_name), m_role(_rhs.m_role),
          m_windowName(_rhs.m_windowName), m_showOption(_rhs.m_showOption) {}

    AppData &operator=(const AppData &_rhs) {
        m_empty = _rhs.m_empty;
        m_name = _rhs.m_name;
        m_role = _rhs.m_role;
        m_windowName = _rhs.m_windowName;
        m_showOption = _rhs.m_showOption;
        return *this;
    }

    bool operator==(const AppData &_rhs) const {
        return m_name == _rhs.m_name
                && m_role == _rhs.m_role
                && m_windowName == _rhs.m_windowName
                && m_showOption == _rhs.m_showOption;
    }

    bool operator!=(const AppData &_rhs) const {
        return !operator==(_rhs);
    }

    bool sameRole(const QString &_name, const QString &_role) const {
        return m_name == _name && m_role == _role;
    }

    bool sameRole(const QString &_role) const {
        return m_role == _role;
    }

    bool sameRole(const AppData &_rhs) const {
        return m_name == _rhs.name() && m_role == _rhs.role();
    }

    void clear() {
        *this = AppData();
    }

    bool empty() const { return m_empty; }
    const QString &name() const { return m_name; }
    const QString &role() const { return m_role; }
    const QString &windowName() const { return m_windowName; }
    E_SHOW_OPT showOption() const { return m_showOption; }
    bool isOverlay() const { return m_showOption == E_SHOW_OPT_ADD_OVERLAY; }

    QJsonObject serialize() const {
        QJsonObject o {};
        o["appName"] = m_name;
        o["appRole"] = m_role;
        o["windowName"] = m_windowName;
        o["showOption"] = (int)m_showOption;
        return o;
    }

    static AppData deserialize(const QJsonObject &o) {
        AppData result {};
        result.m_name = o["appName"].toString();
        result.m_role = o["appRole"].toString();
        result.m_windowName = o["windowName"].toString();
        result.m_showOption = (E_SHOW_OPT)o["showOption"].toInt();
        return result;
    }

private:
    bool m_empty;
    QString m_name;
    QString m_role;
    QString m_windowName;
    E_SHOW_OPT m_showOption;
};

Q_DECLARE_METATYPE(AppData)

#endif //APPMSGDEF_H
