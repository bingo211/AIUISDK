#include "aiuimgr.h"
#include <stdio.h>
#include "utils.h"

std::string appid;
std::string appkey;
std::string auth_id;
std::string skills;

Proc_MvsUrlCallback g_mvsUrlCallback;

aiuiMgr::aiuiMgr()
{
    mvs::globalInit();
}

aiuiMgr::~aiuiMgr()
{
    mvs::globalUninit();
}

aiuiMgr *aiuiMgr::instance()
{
    static aiuiMgr aiui_mgr;
    return &aiui_mgr;
}


void __HandlerMessageCallback(const string &data)
{
    if (data.empty()){
        return ;
    }

	//url地址回调
	if (g_mvsUrlCallback){
		g_mvsUrlCallback(data.data(), data.length());
	}

   // mvsResult * result = parseMvsResult(data);
    //printf("rtmpUrl= %s , httpUrl = %s , rtcUrl=%s \n ",result->d.rtmpUrl.data(),result->d.httpUrl.data(),result->d.rtcUrl.data());
  //  delete result;
}

//连接websocket是否成功
void __ConnectionCallback(bool success)
{
   printf("++++++++%d+\n",success);
}

void aiuiMgr::mvs_news_scence(const std::string tags, const std::string &category)
{
    char __req[1024] ={0};
    int ret = _snprintf_s(__req, sizeof(__req), "我想听%s新闻", tags.data());
    __req[ret] = 0;
    appid == DEFAULT_APPID ? vs.sendData(__req,true) : vs.sendRawData(__req,true);
}

void aiuiMgr::mvs_weather_scence(const string &city)
{
    char __req[128] ={0};
    int ret = _snprintf_s(__req, sizeof(__req), "%s天气", city.data());
    __req[ret] = 0;
    appid == DEFAULT_APPID ? vs.sendData(__req,true) : vs.sendRawData(__req,true);
}

int aiuiMgr::init_session(const std::string &mvs_ip,
	                      Proc_MvsUrlCallback cb,
                          const std::string &_skills,
                          const std::string &_appid,
                          const std::string &_appkey,
                          const std::string &_auth_id)
{

    appid = _appid.empty()? DEFAULT_APPID : _appid;
    appkey = _appkey.empty()? DEFAULT_APPKEY : _appkey;
    auth_id = _auth_id.empty()? DEFAULT_AUTH_ID : _auth_id;
    skills = _skills.empty()? DEFAULT_SKILLS : _skills;
	
    g_mvsUrlCallback = cb;

    std::string params = generateParams("720","1280");
    char surl[1024] ={0};
    int ret = _snprintf_s(surl, sizeof(surl), "ws://%s/tuling/mvs/v2/aiui/11111?params=%s", mvs_ip.data(), params.data());
    surl[ret] = 0;

    vs.startConnection(surl,
                       __ConnectionCallback,
                       __HandlerMessageCallback);
}

void aiuiMgr::stop_session()
{
   vs.destroySession();
}
