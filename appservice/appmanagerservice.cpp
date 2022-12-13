#include "appmanagerservice.h"
#include <QDebug>

#include <algorithm>

#include "utils/statisticlogger.h"
#include "appmain.h"

// don't destroy these, (static nodes)
static const QStringList g_kWindowDestroyIgnoreList {
    WIN_NAME_HOME,
    // WIN_NAME_SETTING,
    WIN_NAME_HOME_SETTING,
    WIN_NAME_HOME_EDIT_VIEW,
    // WIN_NAME_RADIO,
    WIN_NAME_RADIO_SPEECHMODE,
    // WIN_NAME_SXM360L,
    WIN_NAME_SXM360L_SPEECHMODE,
    WIN_NAME_SXM360L_VOICESEARCH,
    // WIN_NAME_MEDIA,
    WIN_NAME_MEDIA_SPEECHMODE,
    WIN_NAME_SIDE_PANEL_LEFT,
    WIN_NAME_SIDE_PANEL_RIGHT,
    WIN_NAME_SIDE_PANEL_VIEW,
    WIN_NAME_SIDE_PANEL_VOLUME,
    // WIN_NAME_SIDE_STEPS,
    // WIN_NAME_TOW_BAR,
    // WIN_NAME_TOW_ASSIST,
    WIN_NAME_POPUP,
    WIN_NAME_PHONE,
    WIN_NAME_PHONE_OVERLAY,
    WIN_NAME_PHONE_SPEECHMODE,
    // WIN_NAME_ENG_SCR,
    // WIN_NAME_ECO,
    // WIN_NAME_SPEECH,
    WIN_NAME_SPEECH_SPEECHMODE,
    WIN_NAME_VOICEPURE,
    // WIN_NAME_VOICEPURE_SPEECHMODE,
    WIN_NAME_SPEECHPTT,
    // WIN_NAME_CLIMATE,
    // WIN_NAME_CLIMATE_HARDKEY_BAR,
    // WIN_NAME_SEAT,
    // WIN_NAME_DYNAMICI,
    // WIN_NAME_LIGHTING,
    // WIN_NAME_DRV4X4I,
    // WIN_NAME_DRV4X4I_HARDKEY_BAR,
    WIN_NAME_PHONE_PROJECTION,
    // WIN_NAME_LTL,
    // WIN_NAME_DIMENSION,
    // WIN_NAME_ASI,
    // WIN_NAME_LFL,
    // WIN_NAME_DEPICP,
    // WIN_NAME_EV,
    // WIN_NAME_SETTINGS,
    // WIN_NAME_SOURCESELECTOR,
    WIN_NAME_NAVI_HMI,
    WIN_NAME_NAVI_HMI_SPEECHMODE,
    WIN_NAME_SOTA,
    // WIN_NAME_PARKING,
    WIN_NAME_SYSTEM_POPUP,
    WIN_NAME_POPUP_ALERT,
    WIN_NAME_POPUP_EXCEPT,
    WIN_NAME_POPUP_NORMAL,
    WIN_NAME_SYSTEM_KEYBOARD,
    WIN_NAME_CAMERA,
    WIN_NAME_CAMERA_LSMG,
    WIN_NAME_DCM,
    WIN_NAME_DCR,
    // WIN_NAME_ONLINE_MEDIA,
    // WIN_NAME_ONLINEMEDIA_SPEECHMODE,
    // WIN_NAME_ONLINEMEDIA_ALEXAMODE,
    // WIN_NAME_ONLINEMEDIA_TMALLMODE,
    // WIN_NAME_VALET_MODE,
    // WIN_NAME_NOTIFICATION,
    WIN_NAME_SMART_SETTINGS,
    WIN_NAME_DISCLAIMER,
    // WIN_NAME_DEPARTURE,
    // WIN_NAME_TJP,
    WIN_NAME_GREETINGS,
    // WIN_NAME_STARTUP_WIZARD,
    // WIN_NAME_ACCOUNT,
    // WIN_NAME_ACCOUNT_OVERLAY,
    WIN_NAME_SUPERICP,
    WIN_NAME_LOWERSCREENBLADE,

    WIN_NAME_NAVI_MAP,
    // WIN_NAME_CAMERA_LAYER,
    WIN_NAME_SPLASH,
    WIN_NAME_CCFSETTING,
    WIN_NAME_CONNECTED_MSG,
    WIN_NAME_SOURCEPICKER,
    // WIN_NAME_LOADING_WEBAPP,
    // WIN_NAME_VEHICLECONTROLS,
    // WIN_NAME_VEHICLECONTROLS_DOOR,
    // WIN_NAME_VEHICLECONTROLS_SUSPENSION,
    // WIN_NAME_TEE		,
    // WIN_NAME_SEAT_VIEW_CONTROL,
    // WIN_NAME_ALEXA,
    WIN_NAME_ALEXA_VOICE_CHROME,
    WIN_NAME_ALEXA_VISUAL_FEEDBACK,
    // WIN_NAME_SHOWROOM,
    WIN_NAME_SHOWROOM_SERVICE,
    WIN_NAME_SHOWROOM_TOUCH,
    // WIN_NAME_TRANSPORT_HARDKEY_BAR,
    // WIN_NAME_TMALL,
    WIN_NAME_TMALL_VOICE_CHROME,
    WIN_NAME_TMALL_VISUAL_FEEDBACK,
    WIN_NAME_COMMON_BACKGROUND,
    WIN_NAME_COMMON_CALL_BUBBLE,
    WIN_HMI_COMMON_3D
};

// don't create these
static const QStringList g_kRoleCreationIgnoreList {
    HMI_ROLE_GREETINGS_GOODBYE,
    "/role/greetings/cbw",

    HMI_ROLE_MEDIA_STREAMING_SPOTIFY,
    HMI_ROLE_MEDIA_STREAMING_AUDIBLE,
    HMI_ROLE_MEDIA_STREAMING_TUENIN,
    HMI_ROLE_MEDIA_STREAMING_DEEZER,

    HMI_ROLE_ALEXA_VOICE_CHROME,
    HMI_ROLE_ALEXA_VISUAL_FEEDBACK,

    HMI_ROLE_TMALL_VOICE_CHROME,
    HMI_ROLE_TMALL_VISUAL_FEEDBACK,

    HMI_ROLE_COMMON_CALL_BUBBLE,
    HMI_ROLE_TRANSPORT,
    HMI_ROLE_TRANSPORT_HARDKEY_BAR,
};

static QString simplifyRole(const QString &_roleWithNumber) {
    QString result = _roleWithNumber;
    auto pattern = QRegularExpression("\\d+$");
    return result.replace(pattern, "_XX");
}

void AppManagerService::init()
{
    m_lastShownNormalApp = m_stack->foreground(); // Home

    connect(m_stack, &AppStackManager::sigForegroundAppChanged,
            this, &AppManagerService::onForegroundAppChanged);
    connect(m_stack, &AppStackManager::sigAppStackChanged,
            this, &AppManagerService::onAppStackChanged);

    // resend graph when window is created/destroyed
    connect(WindowService::instance(), &WindowService::sigWindowLifeChanged,
            this, &AppManagerService::onWindowLifeChanged);

    connect(&m_graphDeployThrottler, &Throttler::sigActionTriggered, this, [&]() {
        qDebug("deploying graph...");
        updateGraph();

        static bool isFirstSend = true;
        if (isFirstSend) {
            m_deploy->onBrAppGraphChanged(m_graph);
        }
        // isFirstSend = false;

        if (!StatisticLogger::instance()->isRunning()) {
            // start logging on the first graph update
            // StatisticLogger::instance()->startLogging();
        }

        m_graph.dumpMermaid();
        m_graph.dumpGraphInfo();
    });
}

void AppManagerService::clearAllData()
{
    clearTempData();
    m_graph.clear();
}

void AppManagerService::clearTempData()
{
    m_stack->clear();
    // m_graph.setStaticNodeList(g_kStaticNodes);
}

void AppManagerService::sendInitData()
{
    // TODO: send init data: foreground, stack,... when client connected
    const auto fg = m_stack->foreground();
    m_deploy->onBrForegroundAppChanged(cstr(fg.name()), cstr(fg.role()), fg.isOverlay());
    m_deploy->onBrAppStackChanged(m_stack->appStack());
    m_deploy->onBrAppGraphChanged(m_graph);
}

void AppManagerService::requestStartLogging(int requestID)
{
    AppMain::instance()->clearTempData();
    AppMain::instance()->sendInitData();
    StatisticLogger::instance()->stopLogging();
    StatisticLogger::instance()->startLogging();

    requestToGoApplication(-1, HMI_APP_NAME_GREETINGS, HMI_ROLE_GREETINGS, "init", E_SHOW_OPT_CLEAR_AND_ADD);
    requestToGoApplication(-1, HMI_APP_NAME_HOME, HMI_ROLE_HOME, "init", E_SHOW_OPT_CLEAR_AND_ADD);
}

void AppManagerService::requestStopLogging(int requestID)
{
    StatisticLogger::instance()->stopLogging();
}

void AppManagerService::requestSetMemoryStrategy(int requestID, E_MEMORY_STRATEGY strategy)
{
    Q_UNUSED(requestID);
    qDebug() << "Strategy: " << (int)strategy;
    m_strategy = strategy;

    AppMain::instance()->sendInitData();

    StatisticLogger::instance()->stopLogging();
}

void AppManagerService::requestToRegisterApplication(const int &requestID, const APP_INFO_T &tAppInfo)
{
    const auto makeTable = [](const APP_INFO_T &app) -> QList<QPair<QString, Graph::__RoleStaticInfo>> {
        QString appName = app.strAppBinaryName;
        QString defaultRole = app.strAppRole;
        QString defaultWindowName = app.strAppWindowName;

        QString pairs = app.strHMIRoleWindowPair;
        QList<QPair<QString, Graph::__RoleStaticInfo>> result {};

        // qDebug() << qstr(app.strAppBinaryName);

        if (!defaultRole.isEmpty()) {
            result.append(qMakePair(defaultRole, Graph::__RoleStaticInfo { appName.toStdString(), defaultWindowName.toStdString() }));
        }

        if (pairs.isEmpty()) {
            pairs = defaultRole + "," + appName;
        }

        // template: "roleA,winA:roleB,winB"

        // qDebug() << pairs.size();
        const auto pairList = pairs.split(':');
        QString lastWinName {};

        for (const auto &item : qAsConst(pairList)) {
            const auto p = item.split(',');
            const auto role = simplifyRole(p.at(0));
            auto winName = p.at(1);

            if (role == defaultRole) {
                // we added above
                continue;
            }

            // some apps (ie: climate) put blank on windowName pair,
            // so use defaut windowName
            if (winName.isEmpty()) {
                winName = app.strAppWindowName;
            }

            // OnlineMedia uses trick
            if (winName == "=") {
                winName = lastWinName;
            }

            result.append(qMakePair(role, Graph::__RoleStaticInfo { appName.toStdString(), winName.toStdString() }));
            lastWinName = winName;
        }

        return result;
    };

    const auto table = makeTable(tAppInfo);
    for (const auto &i : table) {
        const auto role = i.first.toStdString();
        if (g_kRoleCreationIgnoreList.contains(qstr(role)))
            continue;

        const auto id = m_graph.getOrCreateId(role);
        m_graph.m_roleInfoLookupTable[id] = i.second;

        // TODO: Temporary patch: set the role as static if the window is static
        if (isStaticWindow(qstr(i.second.windowName))) {
            m_graph.updateNode(id, Graph::NodeFlags::IsStatic, true);
        }
    }
}

void AppManagerService::requestToRegisterApplicationLink(const int &requestID, const APP_LINK_VECTOR_T &vAppLink)
{
    const auto parentRole = simplifyRole(qstr(vAppLink.strAppRole)).toStdString();

    if (vAppLink.strAppRole.empty()) {
        qCritical() << "Empty role:" << qstr(vAppLink.strAppBinaryName)
                    << qstr(vAppLink.strAppRole);

        for (const auto &item : vAppLink.vLinkData) {
            qWarning() << "---" << (item.strAppRole);
        }
        return;
    }
    m_graph.clearEdges(parentRole);

    for (const auto &item : vAppLink.vLinkData) {
        const auto role = simplifyRole(item.strAppRole).toStdString();

        if (role.empty()) {
            qCritical() << "Empty role:" << qstr(vAppLink.strAppRole);
            continue;
        }

        // ignore paths to HOME
        if (role == HMI_ROLE_HOME
                || role == HMI_ROLE_HOME_APPDRAWER) {
            continue;
        }
        // ignore paths to self
        if (role == parentRole) {
            continue;
        }

        m_graph.addEdge(parentRole, Graph::Edge { role, item.eShowOption });
    }

    triggerSendGraph();
}

void AppManagerService::requestToGoApplication(const int &requestID, const char *strAppBinaryName, const char *strAppRole, const char *strIntent, const E_SHOW_OPT &eShowOpt)
{
    const auto role = simplifyRole(strAppRole);
    qDebug() << requestID << strAppBinaryName << role << strIntent << eShowOpt;

    const auto winName = windowName(role);
    const auto fg = m_stack->foreground();

    bool openWhenAlreadyOnForeground = fg.sameRole(strAppBinaryName, strAppRole);

    WindowService::instance()->launchWindow(isStaticWindow(winName)
                                            ? WindowService::WindowType::Static
                                            : WindowService::WindowType::NonStatic,
                                            winName,
                                            openWhenAlreadyOnForeground);

    m_stack->openApp({
                         strAppBinaryName,
                         role,
                         winName,
                         eShowOpt
                     });

    m_deploy->onGoApplicationResult(requestID, E_REQ_RESULT_MSG_OK);
}

void AppManagerService::requestToGoBack(const int &requestID)
{
    qDebug() << requestID;
    const auto fgBefore = m_stack->foreground();
    m_stack->goBack();
    m_deploy->onGoBackResult(requestID, E_REQ_RESULT_MSG_OK);
    const auto fgAfter = m_stack->foreground();

    if (fgBefore != fgAfter) {
        if (fgBefore.isOverlay()) {

        } else {
            // it might get destroyed before
            const auto winName = fgAfter.windowName();
            WindowService::instance()->launchWindow(isStaticWindow(winName)
                                                    ? WindowService::WindowType::Static
                                                    : WindowService::WindowType::NonStatic,
                                                    winName,
                                                    false);
        }
    }
}

void AppManagerService::requestToHideApplication(const int &requestID, const char *strAppName, const char *strAppRole)
{
    const auto role = simplifyRole(strAppRole);
    qDebug() << requestID << role;
    m_stack->hideApp(strAppName, role);
    m_deploy->onHideApplicationResult(requestID, E_REQ_RESULT_MSG_OK);
}

QString AppManagerService::windowName(const QString &_role) const
{
    return qstr(m_graph.windowName(_role.toStdString()));
}

QString AppManagerService::appName(const QString &_role) const
{
    return qstr(m_graph.windowName(_role.toStdString()));
}

void AppManagerService::triggerSendGraph()
{
    m_graphDeployThrottler.trigger();
}

void AppManagerService::updateGraph()
{
    std::vector<int> ids_active {};

    for (const auto &item : m_stack->appStack()) {

        int id = m_graph.getId(stdstr(item.role()));
        if (id < 0) continue;

        ids_active.push_back(id);
    }

    int fgId = m_graph.getId(stdstr(m_stack->foreground().role()));
    if (fgId >= 0)
        ids_active.push_back(fgId);

    auto &graphRef = m_graph.m_graph;
    auto relatives = m_graph.relatives(ids_active);

    qDebug("Graph size: %d, active: %zu, relatives: %zu, fgId: %d",
           m_graph.vertexCount(), ids_active.size(),
           relatives.size(), fgId);

    // reset graph
    for (int i = 0; i < m_graph.vertexCount(); ++i) {
        auto &nodeinfo = graphRef[i].typeInfo.data;
        // nodeinfo.isCreated = false;
        nodeinfo.isActive = false;
        nodeinfo.isForeground = false;
        nodeinfo.isMostFrequentlyUsed = false;
        nodeinfo.isPotential = false;
    }

    // set potential (relatives)
    for (int i : relatives) {
        auto &nodeinfo = graphRef[i].typeInfo.data;
        nodeinfo.isPotential = true;
    }

    // set active
    for (int i : ids_active) {
        auto &nodeinfo = graphRef[i].typeInfo.data;
        nodeinfo.isActive = true;
    }

    // set fg
    if (fgId >= 0)
        graphRef[fgId].typeInfo.data.isForeground = true;

    checkAndDestroyWindow();
}

void AppManagerService::checkAndDestroyWindow()
{
    if (memoryStrategy() != E_STRATEGY_GRAPH)
        return;

    using Level = SystemService::MemoryUsageLevel;
    const Level level = SystemService::instance()->level();

    const auto currentNormalApp = m_stack->currentNormalApp();

    if (level == SystemService::Medium1) return;

    auto &graphRef = m_graph.m_graph;
    QMap<QString, bool> windowsToKeep {};
    // true: keep, false: destroy
    for (const auto &w : WindowService::instance()->createdWindows()) {
        if (g_kWindowDestroyIgnoreList.contains(w))
            windowsToKeep[w] = true;
        else
            windowsToKeep[w] = false;
    }

    // destroy window
    for (int i = 0; i < m_graph.vertexCount(); ++i) {
        const auto &node = graphRef[i];
        auto &nodeinfo = node.typeInfo.data;

        QString keepReason {};
        // if (                                            level == Level::Medium1); // exit at the begining of the function
        if (nodeinfo.isPotential                        && level <= Level::Medium2)
            keepReason = "potential";
        if (nodeinfo.isActive && !nodeinfo.isForeground && level <= Level::Medium3)
            keepReason = "active";
        if (nodeinfo.isStatic)     // always keep static nodes
            keepReason = "static";
        if (nodeinfo.isForeground) // always keep foreground
            keepReason = "foreground";

        auto role = m_graph.getNameFromId(i);
        auto window = qstr(m_graph.windowName(role));

        if (currentNormalApp.sameRole(qstr(role))) {
            keepReason = "foregroundNormal";
        }
        // TODO: don't destroy overlay list

        if (!keepReason.isEmpty() && !window.isEmpty() && windowsToKeep[window] == false) {
            qDebug() << "??? " << qstr(role) << window << " keep reason: " << keepReason;
            windowsToKeep[window] = true;
        }
    }

    int nDestroyed = 0;
    for (const auto &w : windowsToKeep.keys()) {
        if (windowsToKeep[w] == false) {
            Q_ASSERT(!isStaticWindow(w));
            WindowService::instance()->destroyWindow(w);
            nDestroyed++;
        }
    }

    if (nDestroyed > 0) {
        m_deploy->onBrDestroyTriggered(level);
    }
}

void AppManagerService::onForegroundAppChanged()
{
    const auto fg = m_stack->foreground();
    qDebug() << fg.name();
    m_deploy->onBrForegroundAppChanged(cstr(fg.name()), cstr(fg.role()), fg.isOverlay());

    if (memoryStrategy() == E_STRATEGY_HOME) {
        const auto role = m_lastShownNormalApp.role();
        const int id = m_graph.getId(stdstr(role));

        bool isStatic = m_graph.getNodeFlag(id, Graph::NodeFlags::IsStatic);

        if (fg.role() == HMI_ROLE_HOME) {
            qDebug() << "User went Home, last normal app: " << m_lastShownNormalApp.role()
                     << "isStatic:" << isStatic;
            const auto w = windowName(role);

            if (!g_kWindowDestroyIgnoreList.contains(w) && !isStatic) {// not in ignore list
                Q_ASSERT(!isStaticWindow(w));
                WindowService::instance()->destroyWindow(w);
                // m_deploy->onBrDestroyTriggered(SystemService::instance()->level());
                m_deploy->onBrDestroyTriggered(0);
            }
        } else {
            if (fg.showOption() != E_SHOW_OPT_ADD_OVERLAY) {
                m_lastShownNormalApp = fg;
            }
        }
    }

    triggerSendGraph();
}

void AppManagerService::onAppStackChanged()
{
    const auto stack = m_stack->appStack();
    m_deploy->onBrAppStackChanged(stack);
    triggerSendGraph();
}

void AppManagerService::onWindowLifeChanged(const QString &_window, bool _created)
{
    auto roleIds = rolesThatUseWindow(_window);

    for (const int id : roleIds) {
        m_graph.updateNode(id, Graph::NodeFlags::IsCreated, _created);
    }

    triggerSendGraph();
}

bool AppManagerService::isStaticWindow(const QString &_window) const
{
    return g_kWindowDestroyIgnoreList.contains(_window);
}

std::vector<int> AppManagerService::rolesThatUseWindow(const QString &_window) const
{
    std::vector<int> result {};

    for (int i = 0; i < m_graph.vertexCount(); ++i) {
        if (qstr(m_graph.m_roleInfoLookupTable[i].windowName) == _window) {
            result.push_back(i);
        }
    }

    return result;
}
