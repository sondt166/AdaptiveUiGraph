#ifndef APPMANAGERSERVICE_H
#define APPMANAGERSERVICE_H

#include "AppMsgDef.h"
#include "AppNameDef.h"
#include "AppRoleDef.h"
#include "WindowNameDef.h"

#include "interface/service/IBaseAppService.h"
#include "interface/service/BaseAppDeploy.h"

#include "appstackmanager.h"
#include "graph.h"
#include "utils/singleton.h"
#include "utils/throttler.h"

#include "systemservice/systemservice.h"
#include "windowservice/windowservice.h"

#include <QRegularExpression>

static const std::string DOWNLOAD_MANAGER_APP_NAME("jlr.webapp.updateManager");
static const std::string DOWNLOAD_MANAGER_APP_ROLE("jlr.webapp.updateManager");

class AppManagerService : public IBaseAppService
{
    Q_OBJECT
    MAKE_SINGLETON(AppManagerService);
public:
    void init();

    void clearAllData();
    void clearTempData();
    void sendInitData();

    // ----- REQUESTS FROM CLIENT -----
    void requestStartLogging(int requestID) override;
    void requestStopLogging(int requestID) override;
    void requestSetMemoryStrategy(int requestID, E_MEMORY_STRATEGY strategy) override;

    void requestToRegisterApplication(const int& requestID, const APP_INFO_T& tAppInfo) override;
    void requestToGoApplication(const int& requestID, const char* strAppBinaryName, const char* strAppRole, const char* strIntent, const E_SHOW_OPT& eShowOpt) override;

    void requestToGoBack(const int& requestID) override;
    void requestToHideApplication(const int& requestID, const char* strAppName, const char* strAppRole) override;
    /*
     * New interface of App Manager Service
     * It uses for HMI Application to register the link between current HMI Application to others
     * The data is based on requestToGoApplication() logic of each HMI Application
     */
    void requestToRegisterApplicationLink(const int& requestID, const APP_LINK_VECTOR_T& vAppLink) override;

    std::vector<int> rolesThatUseWindow(const QString &_window) const;

    QString windowName(const QString &_role) const;
    QString appName(const QString &_role) const;

    void triggerSendGraph();
    Graph &graph() { return m_graph; }

    void updateGraph();
    void checkAndDestroyWindow();

private slots:
    void onForegroundAppChanged();
    void onAppStackChanged();

    void onWindowLifeChanged(const QString &_window, bool _created);

private:
    E_MEMORY_STRATEGY memoryStrategy() const { return m_strategy; }
    bool isStaticWindow(const QString &_window) const;

private:
    BaseAppDeploy *m_deploy = BaseAppDeploy::instance();
    AppStackManager *m_stack = AppStackManager::instance();

    SystemService *m_system = SystemService::instance();
    WindowService *m_window = WindowService::instance();

    Graph m_graph {};

    Throttler m_graphDeployThrottler {1000};

    AppData m_lastShownNormalApp {};
    E_MEMORY_STRATEGY m_strategy {};
};

#endif // APPMANAGERSERVICE_H
