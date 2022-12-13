#ifndef HMI_ROLE_DEF_H_
#define HMI_ROLE_DEF_H_

//////////////////////////////////////////////////////////////////////////
// Role
//////////////////////////////////////////////////////////////////////////

#define HMI_ROLE_NONE                      ""

// Home (lge.app.home)
#define HMI_ROLE_HOME                      "/role/home"
#define HMI_ROLE_HOME_SETTING              "/role/home/setting"
#define HMI_ROLE_HOME_APPDRAWER            "/role/home/appdrawer"

// Radio (lge.app.radio)
#define HMI_ROLE_RADIO                     "/role/radio"
#define HMI_ROLE_RADIO_AM                  "ent/am"                           // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_AM
#define HMI_ROLE_RADIO_FM                  "ent/fm"                           // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_FM
#define HMI_ROLE_RADIO_DAB                 "ent/dab"                          // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_DAB
#define HMI_ROLE_RADIO_SPEECHMODE          "/role/radio/speechmode"

// SXM360L (lge.app.sxm360l)
#define HMI_ROLE_SXM360L_RADIO             "/role/sxm360l"
#define HMI_ROLE_RADIO_SXM_SAT             "ent/sxm/sat"                      // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_SXM_SAT
#define HMI_ROLE_RADIO_SXM_IP              "ent/sxm/ip"                       // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_BROADCAST_SXM_IP
#define HMI_ROLE_SXM360L_RADIO_SPEECHMODE  "/role/sxm360l/speechmode"
#define HMI_ROLE_SXM360L_RADIO_VOICESEARCH "/role/sxm360l/voicesearch"

// Media (lge.app.media)
#define HMI_ROLE_MEDIA                     "/role/media"
#define HMI_ROLE_MEDIA_USB0                "ent/usb0"                         // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_USB0 
#define HMI_ROLE_MEDIA_USB1                "ent/usb1"                         // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_USB1
#define HMI_ROLE_MEDIA_USB2                "ent/usb2"                         // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_USB2
#define HMI_ROLE_MEDIA_USB3                "ent/usb3"                         // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_USB3
#define HMI_ROLE_MEDIA_USB4                "ent/usb4"                         // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_USB4
#define HMI_ROLE_MEDIA_USB5                "ent/usb5"                         // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_USB5
#define HMI_ROLE_MEDIA_USB6                "ent/usb6"                         // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_USB6
#define HMI_ROLE_MEDIA_USB7                "ent/usb7"                         // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_USB7
#define HMI_ROLE_MEDIA_CARPLAY             "ent/carplay"                      // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_CARPLAY
#define HMI_ROLE_MEDIA_ANDROID_AUTO        "ent/androidauto"                  // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_ANDROID_AUTO
#define HMI_ROLE_MEDIA_BAIDU_CARLIFE       "ent/carlife"                      // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_CARLIFE
#define HMI_ROLE_BT_A2DP                   "ent/bt/a2dp"                      // N/A
#define HMI_ROLE_BT_A2DP0                  "ent/bt/a2dp0"                     // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_BT0
#define HMI_ROLE_BT_A2DP1                  "ent/bt/a2dp1"                     // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_BT1
#define HMI_ROLE_MEDIA_SPEECHMODE          "media/speechmode"

// Online Media (lge.app.onlinemedia)
#define HMI_ROLE_ONLINE_MEDIA              "/role/onlinemedia"
#define HMI_ROLE_ONLINE_MEDIA_SPEECHMODE   "/role/onlinemedia/speechmode"
#define HMI_ROLE_MEDIA_STREAMING_SPOTIFY   "ent/spotify"                      // N/A
#define HMI_ROLE_MEDIA_STREAMING_AUDIBLE   "ent/audible"                      // N/A
#define HMI_ROLE_MEDIA_STREAMING_TUENIN    "ent/tuenin"                       // N/A
#define HMI_ROLE_MEDIA_STREAMING_DEEZER    "ent/deezer"                       // N/A
#define HMI_ROLE_ONLINE_MEDIA_ALEXAMODE    "/role/onlinemedia/alexamode"
#define HMI_ROLE_ONLINE_MEDIA_TMALLMODE    "/role/onlinemedia/tmallmode"

#define HMI_ROLE_MEDIA_STREAMING0          "ent/sm0"                          // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_ONLINEMEDIA0
#define HMI_ROLE_MEDIA_STREAMING1          "ent/sm1"                          // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_ONLINEMEDIA1
#define HMI_ROLE_MEDIA_STREAMING2          "ent/sm2"                          // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_ONLINEMEDIA2
#define HMI_ROLE_MEDIA_STREAMING3          "ent/sm3"                          // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_ONLINEMEDIA3
#define HMI_ROLE_MEDIA_STREAMING4          "ent/sm4"                          // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_ONLINEMEDIA4
#define HMI_ROLE_MEDIA_STREAMING5          "ent/sm5"                          // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_ONLINEMEDIA5
#define HMI_ROLE_MEDIA_STREAMING6          "ent/sm6"                          // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_ONLINEMEDIA6
#define HMI_ROLE_MEDIA_STREAMING7          "ent/sm7"                          // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_ONLINEMEDIA7
#define HMI_ROLE_MEDIA_STREAMING8          "ent/sm8"                          // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_ONLINEMEDIA8
#define HMI_ROLE_MEDIA_STREAMING9          "ent/sm9"                          // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_ONLINEMEDIA9
#define HMI_ROLE_MEDIA_STREAMING10         "ent/sm10"                         // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_ONLINEMEDIA10
#define HMI_ROLE_MEDIA_STREAMING11         "ent/sm11"                         // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_ONLINEMEDIA11
#define HMI_ROLE_MEDIA_STREAMING12         "ent/sm12"                         // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_ONLINEMEDIA12
#define HMI_ROLE_MEDIA_STREAMING13         "ent/sm13"                         // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_ONLINEMEDIA13
#define HMI_ROLE_MEDIA_STREAMING14         "ent/sm14"                         // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_ONLINEMEDIA14
#define HMI_ROLE_MEDIA_STREAMING15         "ent/sm15"                         // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_ONLINEMEDIA15
#define HMI_ROLE_MEDIA_STREAMING16         "ent/sm16"                         // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_ONLINEMEDIA16
#define HMI_ROLE_MEDIA_STREAMING17         "ent/sm17"                         // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_ONLINEMEDIA17
#define HMI_ROLE_MEDIA_STREAMING18         "ent/sm18"                         // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_ONLINEMEDIA18
#define HMI_ROLE_MEDIA_STREAMING19         "ent/sm19"                         // Matched Entertainment Audio Source ID : E_AUDIO_TYPE_MEDIA_ONLINEMEDIA19

// Side Steps (lge.app.sidesteps)
#define HMI_ROLE_SIDESTEPS                 "/role/sidesteps"

// Phone (lge.app.phone)
#define HMI_ROLE_PHONE                     "/role/phone"
#define HMI_ROLE_PHONE_OVERLAY             "/role/phone/overlay"
#define HMI_ROLE_PHONE_SPEECHMODE          "/role/phone/speechmode"

// Connected Msg
#define HMI_ROLE_CONNECTED_MSG             "/role/connectedmsg"

#define HMI_ROLE_SOURCEPICKER              "/role/sourcepicker"

// Eco (lge.app.eco)
#define HMI_ROLE_ECO                       "/role/eco"

// Engineering Screen (lge.app.engscr)
#define HMI_ROLE_ENG_SCR                   "/role/engineering"

// Speech (lge.app.speech)
#define HMI_ROLE_SPEECH                    "/role/speech"
#define HMI_ROLE_SPEECH_SPEECHMODE         "/role/speech/speechmode"

// Voice Pure (lge.app.voicepure)
#define HMI_ROLE_VOICEPURE                 "/role/voicepure"
#define HMI_ROLE_VOICEPURE_SPEECHMODE      "/role/voicepure/speechmode"

// Speech PTT
#define HMI_ROLE_SPEECHPTT                 "/role/speechptt"                    // will be deprecated.
#define HMI_ROLE_SPEECHPTT_BORROWMODE      "/role/speechptt/borrowmode"         // will be deprecated.

// Seat (lge.app.seat)
#define HMI_ROLE_SEAT                      "/role/seat"
#define HMI_ROLE_SEAT_VIEW_CONTROL         "/role/seat/viewcontrol"
#define HMI_ROLE_SEAT_BY_HARDKEY           "/role/seat_hardkey"
#define HMI_ROLE_HAPTIC_SEAT               "/role/haptic_seat"

// Climate (lge.app.climate)
#define HMI_ROLE_CLIMATE                   "/role/climate"
#define HMI_ROLE_CLIMATE_PRECONDITION_NOW  "/role/climate/precon_now"
#define HMI_ROLE_CLIMATE_HARDKEY_BAR       "/role/climate/hardkeybar"
#define HMI_ROLE_CLIMATE_BY_HARDKEY        "/role/climate_hardkey"
#define HMI_ROLE_CLIMATE_VENTS             "/role/climate/vents"
#define HMI_ROLE_CLIMATE_AIR_QUALITY       "/role/climate/air_quality"
#define HMI_ROLE_CLIMATE_ICP_DRAWER        "/role/climate/icpdrawer"
// Dynamic i (lge.app.dynamici)
#define HMI_ROLE_DYNAMICI                  "/role/dynamici"

// Ambient Lighting (lge.app.lighting)
#define HMI_ROLE_LIGHTING                  "/role/lighting"

// Drv4x4i (lge.app.drv4x4i)
#define HMI_ROLE_DRV4X4I                   "/role/drv4x4i"
#define HMI_ROLE_DRV4X4I_CTR               "/role/drv4x4i/ctr"
#define HMI_ROLE_DRV4X4I_HARDKEY_BAR       "/role/drv4x4i/hardkeybar"
#define HMI_ROLE_DRV4X4I_ICP_DRAWER        "/role/drv4x4i/icpdrawer"
#define HMI_ROLE_DRV4X4I_WADE_SENSING      "/role/drv4x4i/wadesensing"
#define HMI_ROLE_DRV4X4I_TR_MODES          "/role/drv4x4i/trmodes"
#define HMI_ROLE_DRV4X4I_RIDE_HEIGHT       "/role/drv4x4i/rideheight"
// Low Traction Launch (lge.app.ltl)
#define HMI_ROLE_LTL                       "/role/ltl"

// Dimension (lge.app.dimension)
#define HMI_ROLE_DIMENSION                 "/role/dimension"

// ASI (lge.app.asi)
#define HMI_ROLE_ASI                       "/role/asi"

// LFL (lge.app.lfl)
#define HMI_ROLE_LFL                       "/role/lfl"

// Dep ICP (lge.app.depicp)
#define HMI_ROLE_DEPICP                    "/role/depicp"

// Ev (lge.app.ev)
#define HMI_ROLE_EV                        "/role/ev"
#define HMI_ROLE_EV_DEEP_CLEANING          "/role/ev/deepcleaning"

// Source Selector (lge.app.sourceselector)
#define HMI_ROLE_SOURCESELECTOR            "/role/sourceselector"
#define HMI_ROLE_SOURCESELECTOR_AA         "/role/sourceAndroidAuto"
#define HMI_ROLE_SOURCESELECTOR_CARPLAY    "/role/sourceCarPlay"
#define HMI_ROLE_SOURCESELECTOR_BAIDU      "/role/sourceBaidu"

// Driver Condition Monitoring (lge.app.dcm)
#define HMI_ROLE_DCM                       "/role/dcm"

// Driver Condition Response (lge.app.dcr)
#define HMI_ROLE_DCR                       "/role/dcr"

// Parking (lge.app.parking)
#define HMI_ROLE_PARKING                   "/role/parking"

// Camera (lge.app.camera)
#define HMI_ROLE_CAMERA                    "/role/camera"
#define HMI_ROLE_CAMERA_LSMG               "/role/camera/lsmg"

// Tow bar (lge.app.towbar)
#define HMI_ROLE_TOWBAR                    "/role/towbar"

// Tow assist
#define HMI_ROLE_TOWASSIST                 "/role/towassist"

// Valet Mode (lge.app.valetmode)
#define HMI_ROLE_VALET_MODE                "/role/valetmode"

// Smart Setting (lge.app.smartsettings)
#define HMI_ROLE_SMART_SETTINGS            "/role/smartsettings"

// Disclaimer (lge.app.disclaimer)
#define HMI_ROLE_DISCLAIMER                "/role/disclaimer"

// CCF Setting (lge.app.ccfsetting)
#define HMI_ROLE_CCFSETTING                "/role/ccfsetting"

// System Popup (lge.framework.system.popup)
#define HMI_ROLE_POPUP                     "/role/popup"

// System Keyboard (lge.framework.system.keyboard)
#define HMI_ROLE_KEYBOARD                  "/role/keyboard"

// Side Panel (lge.app.sidepanel)
#define HMI_ROLE_SIDEPANEL                 "/role/sidepanel"

// Departure (lge.app.departure)
#define HMI_ROLE_DEPARTURE                 "/role/departure"

// Traffic Jam Pilot(lge.app.tjp)
#define HMI_ROLE_TJP                       "/role/tjp"

// Vehicle Controls(lge.app.vehiclecontrols)
#define HMI_ROLE_VEHICLECONTROLS           	"/role/vehiclecontrols"
#define HMI_ROLE_VEHICLECONTROLS_DOORHARDKEY    "/role/vehiclecontrols/doorhardkey"
#define HMI_ROLE_VEHICLECONTROLS_SUSPENSIONHARDKEY    "/role/vehiclecontrols/suspensionhardkey"

// Tailge Experience Event(lge.app.tee)
#define HMI_ROLE_TEE		          "/role/tee"

#define HMI_ROLE_DRIVER_ASSISTANCE          "/role/driver_assistance"

#define HMI_ROLE_LOWERSCREENBLADE          "/role/lowerscreenblade"

#define HMI_ROLE_LOADING_WEBAPP            "/role/loading/webapp"

#define HMI_ROLE_TRANSPORT                 "/role/transport"
#define HMI_ROLE_TRANSPORT_HARDKEY_BAR     "/role/transport/hardkeybar"

// Alexa (lge.app.alexa)
#define HMI_ROLE_ALEXA                     "/role/alexa"
#define HMI_ROLE_ALEXA_VOICE_CHROME        "/role/alexa/voicechrome"
#define HMI_ROLE_ALEXA_VISUAL_FEEDBACK     "/role/alexa/visualfeedback"

// Showroom(lge.app.showroom)
#define HMI_ROLE_SHOWROOM                  "/role/showroom"
#define HMI_ROLE_SHOWROOM_ACTIVE           "/role/showroom/active"
#define HMI_ROLE_SHOWROOM_TOUCH            "/role/showroom/touch"

// Tmall Genie(lge.app.tmall)
#define HMI_ROLE_TMALL                     "/role/tmall"
#define HMI_ROLE_TMALL_VOICE_CHROME        "/role/tmall/voicechrome"
#define HMI_ROLE_TMALL_VISUAL_FEEDBACK     "/role/tmall/visualfeedback"

// Unknown process (It doesn't register to the application service.)
#define HMI_ROLE_RADIO_DRM                 "/role/radio/drm"                    // Matched Entertainment Audio Source ID : E_RES_BROADCAST_DRM
#define HMI_ROLE_RADIO_CONNECTEDRADIO_IP   "/role/radio/connectedradio/ip"      // Matched Entertainment Audio Source ID : E_RES_BROADCAST_CONNECTEDRADIO_IP
#define HMI_ROLE_RADIO_ISDBT               "/role/radio/isdbt"                  // Matched Entertainment Audio Source ID : E_RES_BROADCAST_ISDBT
#define HMI_ROLE_RADIO_FM_NEWS             "/role/radio/fm/news"                // Matched Entertainment Audio Source ID : E_RES_BROADCAST_FM_NEWS
#define HMI_ROLE_RADIO_FM_TA               "/role/radio/fm/ta"                  // Matched Entertainment Audio Source ID : E_RES_BROADCAST_FM_TA
#define HMI_ROLE_RADIO_FM_ALARM            "/role/radio/fm/alarm"               // Matched Entertainment Audio Source ID : E_RES_BROADCAST_FM_ALARM
#define HMI_ROLE_RADIO_DAB_ANNOUNCEMENT    "/role/radio/dab/announcement"       // Matched Entertainment Audio Source ID : E_RES_BROADCAST_DAB_ANNOUNCEMENT
#define HMI_ROLE_TTS_EMAIL                 "/role/tts/email"                    // Matched Entertainment Audio Source ID : E_RES_TTS_EMAIL
#define HMI_ROLE_TTS_SMS                   "/role/tts/sms"                      // Matched Entertainment Audio Source ID : E_RES_TTS_SMS
#define HMI_ROLE_SETTINGS                  "/role/settings"
#define HMI_ROLE_SETTINGS_AUDIO            "/role/settings/audio"
#define HMI_ROLE_SETTINGS_BT               "/role/settings/bt"
#define HMI_ROLE_PHONE_PROJECTION          "/role/phoneprojection"
#define HMI_ROLE_CARPLAY                   "/role/carplay"
#define HMI_ROLE_ANDROID_AUTO              "/role/androidauto"
#define HMI_ROLE_CARLIFE                   "/role/carlife"
#define HMI_ROLE_IN_CONTROL_APPS           "/role/incontrolapps"
#define HMI_ROLE_NAVIGATION                "/role/navigation"
#define HMI_ROLE_NAVIGATION_SPEECHMODE     "/role/navigation/speechmode"
#define HMI_ROLE_NOTIFICATION              "/role/notification"
#define HMI_ROLE_SOTA                      "/role/sota"
#define HMI_ROLE_GREETINGS                 "/role/greetings"
#define HMI_ROLE_GREETINGS_WELCOME         "/role/greetings/welcome"
#define HMI_ROLE_GREETINGS_GOODBYE         "/role/greetings/goodbye"
#define HMI_ROLE_STARTUP_WIZARD            "/role/startupwizard"
#define HMI_ROLE_ACCOUNT_STARTUP           "/role/account/startup"
#define HMI_ROLE_ACCOUNT_PROFILE           "/role/account/profile"
#define HMI_ROLE_ACCOUNT_OVERLAY           "/role/account/overlay"
#define HMI_ROLE_SUPER_ICP                 "/role/supericp"
#define HMI_ROLE_COMUI                     "/role/comui"
#define HMI_ROLE_COMMON_CALL_BUBBLE        "/role/commonCallBubble"

// For Test
#define HMI_ROLE_TEST_APP1                 "/role/testapp1"
#define HMI_ROLE_TEST_APP2                 "/role/testapp2"
#define HMI_ROLE_TEST_APP3                 "/role/testapp3"
#define HMI_ROLE_TEST_APP4                 "/role/testapp4"
#define HMI_ROLE_TEST_APP5                 "/role/testapp5"

#endif //HMI_ROLE_DEF_H_
