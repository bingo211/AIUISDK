#ifndef UTILS_H
#define UTILS_H
#include <vector>
#include "base64.h"
#include <chrono>
#include <sstream>
#include "MyMD5.h"

using namespace  std::chrono;
using namespace  std;

//const static std::string appid = "6012b116";
//const static std::string appkey = "4759acceaf738d7aa979836171a08770";
//const static std::string auth_id = "7fc98c95701ff3253fa4ca4d979fca65";

extern std::string appid;
extern std::string appkey;
extern std::string auth_id;
extern std::string skills;

#define DEFAULT_APPID "5e83faea"
#define DEFAULT_APPKEY "170405a5101847034d2ff4bb7c2e38bb"
#define DEFAULT_AUTH_ID "7fc98c95701ee3253fa4ca4d979fca65"
#define DEFAULT_SKILLS "main_box"

const static std::string _hostname = "content.xfyun.cn";
const static std::string weather_request = "/weather/query?";
const static std::string news_request = "/news/query?";

struct newsRequset {
   std::string name;
   std::string tags;
   std::string category;
   std::string type;
   std::string date;
};

//实时新闻
struct newResult{
   std::string publishTime;
   std::string img;
   std::string author;
   std::string description;
   std::string publishSource;
   std::string source;
   std::string type;
   std::string hot;
   std::string content;
   std::string url;
   std::string tags;
   std::string actor;
   std::string name;
   std::string category;
};

//weather 场景数据输入
struct weatherRequest{
   std::string city;
   std::string gps;
   std::string ip;
};

//天气技能
struct weatherResult {
   std::string date;
   std::string tempLow;
   std::string weatherType;
   std::string img;
   std::string week;
   std::string airData;
   std::string city;
   std::string windLevel;
   std::string date_for_voice;
   std::string weather;
   std::string humidity;
   std::string warning;

   struct __exp {
     struct __ct {
         std::string expName;
         std::string level;
         std::string prompt;
     }ct;

     struct __dy {
         std::string expName;
         std::string level;
         std::string prompt;
     }dy;

     struct __gm {
         std::string expName;
         std::string level;
         std::string prompt;
     }gm;

     struct __jt {
         std::string expName;
         std::string level;
         std::string prompt;
     }jt;

     struct __tr {
         std::string expName;
         std::string level;
         std::string prompt;
     }tr;

     struct __uv {
         std::string expName;
         std::string level;
         std::string prompt;
     }uv;

     struct __xc {
         std::string expName;
         std::string level;
         std::string prompt;
     }xc;

     struct __yd {
         std::string expName;
         std::string level;
         std::string prompt;
     }yd;

   }exp;

   int dateLong;
   std::string airQuality;
   int temp;
   std::string weatherDescription;
   std::string weatherDescription3;
   std::string pm25;
   std::string weatherDescription7;
   std::string tempRange;
   std::string tempHigh;
   std::string lastUpdateTime;
   std::string wind;
};

std::string generateParams(const std::string &height, const std::string &width);
//释放结果字段
// mvsResult* parseMvsResult(const std::string &data);

std::vector<newResult> parseNewsResult(const std::string &cjson);

std::vector<weatherResult> parseWeatherResult(const std::string &cjson);

inline int64_t getTimeStamp()
{
    system_clock::duration d = system_clock::now().time_since_epoch();
    milliseconds mil = duration_cast<milliseconds>(d);
    return mil.count();
}

inline std::string token(int64_t stamp) {
    ostringstream oss;
    oss << appid;
    oss << appkey;
    oss << stamp;

    string _result = {0};
    _result.resize(128);
    unsigned char *p = (unsigned char*)_result.data();
    mymd5::get_md5_value(oss.str().data(),oss.str().length(),p);
    _result.resize(strlen((char*)p));

    return  _result;
}

inline int64_t getTimeStamp2()
{
    system_clock::duration d = system_clock::now().time_since_epoch();
    milliseconds mil = duration_cast<milliseconds>(d);
    return mil.count() / 1000;
}

inline std::string token2(int64_t stamp , const std::string &params){
    ostringstream oss;
    oss << appkey << stamp << params;
    string _result = {0};
    _result.resize(128);

    unsigned char *p = (unsigned char*)_result.data();
    mymd5::get_md5_value(oss.str().data(),oss.str().length(),p);
    _result.resize(strlen((char*)p));

    return  _result;
}


#endif // UTILS_H
