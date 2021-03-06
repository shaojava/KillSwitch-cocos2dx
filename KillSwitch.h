//
//  KillSwitch.h
//  XmasCracker
//
//  Created by Dan on 3/12/2014.
//
//

#ifndef __XmasCracker__KillSwitch__
#define __XmasCracker__KillSwitch__

#include "cocos2d.h"
#include "external/json/document.h"
#include "network/HttpClient.h"
#include "ui/CocosGUI.h"

#include "ModalLayer.h"

class KillSwitch
{
public:
    ~KillSwitch();
    
    static KillSwitch& getInstance()
    {
        static KillSwitch instance;    // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }
    
    void loadConfig(const std::string& p_sConfigURL);
    
    int getBuildNumber();
    std::string getVersionNumber();
    std::string getAppName();
    
private:
    rapidjson::Document m_jsonConfig;
    
    std::string m_sConfigURL;
    std::string m_sAppUpdateLink;
    std::string m_sMaintenanceMessage;
    
    int         m_iAppVersionCurrent;
    int         m_iAppVersionMin;
    
    bool        m_bMaintenanceMode;
    bool        m_bConfigLoading;
    
    ModalLayer  *   m_pMessageLayer;
    
    KillSwitch();
    // Dont forget to declare these two. You want to make sure they
    // are unaccessable otherwise you may accidently get copies of
    // your singleton appearing.
    KillSwitch(KillSwitch const&);            // Don't Implement
    void operator=(KillSwitch const&);
    
    void downloadConfig();
    void parseConfig();
    void checkConfig();
    void flipKillSwitch();
    
    void createMessageLayer();
    void showMessage(const std::string& p_sMessage);
    
    void onHttpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    void onButtonPress(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
};

#endif /* defined(__XmasCracker__KillSwitch__) */
