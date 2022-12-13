#ifndef VERTEXGROUNDRULE_H
#define VERTEXGROUNDRULE_H

// This file defines the graph numbering rule when construct the graph with the system information

enum VertexNumber {
/*
 * This class defines the numbering of "source" vertex
 * The "source" vertex is the vertex which has relationships with all other vertexes in the graph
 * In P-IVI system, there are three source vertex: Home, Camera & User Hardkey
 * For future development, it can be extended based on the change requests.
 */
    E_VERTEX_NONE = -1,

    E_SOURCE_VERTEX_WELCOME,                // WIN_NAME_GREETINGS             "win_hmi_greetings"
    E_SOURCE_VERTEX_HOME,
    E_SOURCE_VERTEX_CAMERA,                 // WIN_NAME_CAMERA                "win_hmi_camera"
    E_SOURCE_VERTEX_USER_HARD_KEY,
    E_SOURCE_VERTEX_MAX = 20
/*
 * This class defines the numbering of non-overlay vertex
 * It is based on the concept of non-overlay HMI Application in P-IVI system,
 * when the HMI application content is displayed with the side bar and driver bar of Home HMI
 * This data is linked to window name file as WindowNameDef.h
 * http://vopengrok.lge.com:8122/xref/proteus_release/LGE/ICCM/framework/common/hmiconfig/WindowNameDef.h
 */
    E_NON_OVERLAY_VERTEX_RADIO = 21,        // WIN_NAME_RADIO                 "win_hmi_radio"
    E_NON_OVERLAY_VERTEX_SXM360L,           // WIN_NAME_SXM360L               "win_hmi_sxm360l"
    E_NON_OVERLAY_VERTEX_MEDIA,             // WIN_NAME_MEDIA                 "win_hmi_media"
    E_NON_OVERLAY_VERTEX_SIDE_STEPS,        // WIN_NAME_SIDE_STEPS            "win_hmi_sidesteps"
    E_NON_OVERLAY_VERTEX_TOW_BAR,           // WIN_NAME_TOW_BAR               "win_hmi_towbar"
    E_NON_OVERLAY_VERTEX_TOW_ASSIST,        // WIN_NAME_TOW_ASSIST            "win_hmi_towassist"
    E_NON_OVERLAY_VERTEX_PHONE,             // WIN_NAME_PHONE                 "win_hmi_phone"
    E_NON_OVERLAY_VERTEX_ENG_SCR,           // WIN_NAME_ENG_SCR               "win_hmi_engscr"
    E_NON_OVERLAY_VERTEX_ECO,               // WIN_NAME_ECO                   "win_hmi_eco"
    E_NON_OVERLAY_VERTEX_SPEECH,            // WIN_NAME_SPEECH                "win_hmi_speech"
    E_NON_OVERLAY_VERTEX_CLIMATE,           // WIN_NAME_CLIMATE               "win_hmi_climate"
    E_NON_OVERLAY_VERTEX_SEAT,              // WIN_NAME_SEAT                  "win_hmi_seat"
    E_NON_OVERLAY_VERTEX_DYNAMICI,          // WIN_NAME_DYNAMICI              "win_hmi_dynamici"
    E_NON_OVERLAY_VERTEX_DRV4X4I ,          // WIN_NAME_DRV4X4I               "win_hmi_drv4x4i"
    E_NON_OVERLAY_VERTEX_PHONE_PROJECTION,  // WIN_NAME_PHONE_PROJECTION      "win_hmi_phoneprojection"
    E_NON_OVERLAY_VERTEX_LTL,               // WIN_NAME_LTL                   "win_hmi_ltl"
    E_NON_OVERLAY_VERTEX_DIMENSION,         // WIN_NAME_DIMENSION             "win_hmi_dimension"
    E_NON_OVERLAY_VERTEX_ASI,               // WIN_NAME_ASI                   "win_hmi_asi"
    E_NON_OVERLAY_VERTEX_EV,                // WIN_NAME_EV                    "win_hmi_ev"
    E_NON_OVERLAY_VERTEX_SOURCESELECTOR,    // WIN_NAME_SOURCESELECTOR        "win_hmi_sourceselector"
    E_NON_OVERLAY_VERTEX_NAVI_HMI,          // WIN_NAME_NAVI_HMI              "win_hmi_navi"
    E_NON_OVERLAY_VERTEX_PARKING,           // WIN_NAME_PARKING               "win_hmi_parking"
    E_NON_OVERLAY_VERTEX_ONLINE_MEDIA,      // WIN_NAME_ONLINE_MEDIA          "win_hmi_onlinemedia"
    E_NON_OVERLAY_VERTEX_VALET_MODE,        // WIN_NAME_VALET_MODE            "win_hmi_valetmode"
    E_NON_OVERLAY_VERTEX_DEPARTURE,         // WIN_NAME_DEPARTURE             "win_hmi_departure"
    E_NON_OVERLAY_VERTEX_STARTUP_WIZARD,    // WIN_NAME_STARTUP_WIZARD        "win_hmi_startupwizard"
    E_NON_OVERLAY_VERTEX_ACCOUNT,           // WIN_NAME_ACCOUNT               "win_hmi_account"
    E_NON_OVERLAY_VERTEX_LOADING_WEBAPP,    // WIN_NAME_LOADING_WEBAPP        "win_hmi_loadingwebapp"
    E_NON_OVERLAY_VERTEX_TEE,               // WIN_NAME_TEE                   "win_hmi_tee"
    E_NON_OVERLAY_VERTEX_ALEXA,             // WIN_NAME_ALEXA                 "win_hmi_alexa"
    E_NON_OVERLAY_VERTEX_TMALL,             // WIN_NAME_TMALL                 "win_hmi_tmall"
    E_NON_OVERLAY_VERTEX_MAX = 150

/*
 * This class defines the numbering of overlay vertex
 * It is based on the concept of overlay HMI Application in P-IVI system,
 * when the HMI application content is displayed over the side bar and driver bar
 * This data is linked to window name file as WindowNameDef.h
 * http://vopengrok.lge.com:8122/xref/proteus_release/LGE/ICCM/framework/common/hmiconfig/WindowNameDef.h
 */
    E_OVERLAY_VERTEX_RADIO_SPEECHMODE = 200,        // WIN_NAME_RADIO_SPEECHMODE            "win_hmi_radio_speechmode"
    E_OVERLAY_VERTEX_SXM360L_SPEECHMODE,            // WIN_NAME_SXM360L_SPEECHMODE          "win_hmi_sxm360l_speechmode"
    E_OVERLAY_VERTEX_SXM360L_VOICESEARCH,           // WIN_NAME_SXM360L_VOICESEARCH         "win_hmi_sxm360l_voicesearch"
    E_OVERLAY_VERTEX_MEDIA_SPEECHMODE ,             // WIN_NAME_MEDIA_SPEECHMODE            "win_hmi_media_speechmode"
    E_OVERLAY_VERTEX_PHONE_SPEECHMODE,              // WIN_NAME_PHONE_SPEECHMODE            "win_hmi_phone_speechmode"
    E_OVERLAY_VERTEX_SPEECH_SPEECHMODE,             // WIN_NAME_SPEECH_SPEECHMODE           "win_hmi_speech_speechmode"
    E_OVERLAY_VERTEX_SPEECHPTT ,                    // WIN_NAME_SPEECHPTT                   "win_hmi_speechptt"
    E_OVERLAY_VERTEX_CLIMATE_HARDKEY_BAR ,          // WIN_NAME_CLIMATE_HARDKEY_BAR         "win_hmi_climate_hardkeybar"
    E_OVERLAY_VERTEX_DRV4X4I_HARDKEY_BAR ,          // WIN_NAME_DRV4X4I_HARDKEY_BAR         "win_hmi_drv4x4i_hardkeybar"
    E_OVERLAY_VERTEX_SETTINGS,                      //                                      "win_hmi_setting"
    E_OVERLAY_VERTEX_NAVI_HMI_SPEECHMODE,           // WIN_NAME_NAVI_HMI_SPEECHMODE         "win_hmi_navi_speechmode"
    E_OVERLAY_VERTEX_SOTA,                          // WIN_NAME_SOTA                        "win_hmi_sota"
    E_OVERLAY_VERTEX_CAMERA_LSMG,                   // WIN_NAME_CAMERA_LSMG                 "win_hmi_camera_lsmg"
    E_OVERLAY_VERTEX_ONLINEMEDIA_SPEECHMODE,        // WIN_NAME_ONLINEMEDIA_SPEECHMODE      "win_hmi_onlinemedia_speechmode"
    E_OVERLAY_VERTEX_ONLINEMEDIA_ALEXAMODE,         // WIN_NAME_ONLINEMEDIA_ALEXAMODE       "win_hmi_onlinemedia_alexamode"
    E_OVERLAY_VERTEX_ONLINEMEDIA_TMALLMODE,         // WIN_NAME_ONLINEMEDIA_TMALLMODE       "win_hmi_onlinemedia_tmallmode"
    E_OVERLAY_VERTEX_NOTIFICATION ,                 // WIN_NAME_NOTIFICATION                "win_hmi_notification"
    E_OVERLAY_VERTEX_ACCOUNT_OVERLAY ,              // WIN_NAME_ACCOUNT_OVERLAY             "win_hmi_account_overlay"
    E_OVERLAY_VERTEX_VEHICLECONTROLS,               // WIN_NAME_VEHICLECONTROLS             "win_hmi_vehiclecontrols"
    E_OVERLAY_VERTEX_VEHICLECONTROLS_DOOR,          // WIN_NAME_VEHICLECONTROLS_DOOR        "win_hmi_vehiclecontrols_door_hardkeybar"
    E_OVERLAY_VERTEX_VEHICLECONTROLS_SUSPENSION,    // WIN_NAME_VEHICLECONTROLS_SUSPENSION  "win_hmi_vehiclecontrols_suspension_hardkeybar"
    E_OVERLAY_VERTEX_SEAT_VIEW_CONTROL,             // WIN_NAME_SEAT_VIEW_CONTROL           "win_hmi_seat_view_control_hardkeybar"
    E_OVERLAY_VERTEX_MAX = 300
};

#endif // VERTEXGROUNDRULE_H
