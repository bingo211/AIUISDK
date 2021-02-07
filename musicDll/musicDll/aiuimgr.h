#ifndef AIUIMGR_H
#define AIUIMGR_H

#include "mvs.h"
#include "util.h"

class aiuiMgr
{
public:
    aiuiMgr();
    virtual ~aiuiMgr();
    static aiuiMgr* instance();
    /**
     * @brief mvs_news_scence   开启news新闻场景
     * @param tags
     * @param category
     */
    void mvs_news_scence(const std::string tags, const std::string &category);
    /**
     * @brief mvs_weather_scence   获取城市天气
     * @param city 城市
     */
    void mvs_weather_scence(const std::string &city);

    /**
     * @brief init_session 初始化虚拟形象
     * @param mvs_ip
     * @param __skills 技能名称
     * @param _appid
     * @param _appkey
     * @param _auth_id
     * @return
     */
	int init_session(const std::string &mvs_ip,
					 Proc_MvsUrlCallback cb,
                     const std::string &_skills="",
                     const std::string &_appid="",
                     const std::string &_appkey="",
                     const std::string &_auth_id="");
    /**
     * @brief stop_session
     * 停止虚拟形象session
     */
    void stop_session();
private:
     mvs vs;
     //aiui ui;
};

#endif // AIUIMGR_H
