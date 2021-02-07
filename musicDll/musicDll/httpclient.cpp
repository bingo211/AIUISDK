#include "httpclient.h"
#include <chrono>
#include <sstream>
#include <iostream>
#include "MyMD5.h"
#include "picojson.h"


using namespace  std::chrono;
using namespace  std;
#pragma warning(disable:4996)

inline int64_t getTimeStamp()
{
	system_clock::duration d = system_clock::now().time_since_epoch();
	milliseconds mil = duration_cast<milliseconds>(d);
	return mil.count();
}

inline std::string token(int64_t stamp) {
	ostringstream oss;
	oss << appid << appkey << stamp;
	string _result;
	_result.resize(128);
	unsigned char *p = (unsigned char*)_result.data();
	mymd5::get_md5_value(oss.str().data(), oss.str().length(), p);
	_result.resize(strlen((char*)p));

	return  _result;
}

string gbk_to_utf8(string gbkStr)
{
	string outUtf8 = "";
	int n = MultiByteToWideChar(CP_ACP, 0, gbkStr.c_str(), -1, NULL, 0);
	WCHAR *str1 = new WCHAR[n];
	MultiByteToWideChar(CP_ACP, 0, gbkStr.c_str(), -1,str1, n);
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
	char *str2 = new char[n];
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
	outUtf8 = str2;
	delete[]str1;
	str1 = NULL;
	delete[]str2;
	str2 = NULL;
	return outUtf8;
}


std::string utf8_to_gbk(const std::string &str_utf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, str_utf8.c_str(), -1, NULL, 0);
	uint16_t *short_gbk = new uint16_t[len + 1];
	memset(short_gbk, 0, len * 2 + 2);

	MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char *> (str_utf8.c_str()),
		-1, reinterpret_cast<wchar_t *> (short_gbk), len);

	len = WideCharToMultiByte(CP_ACP, 0, reinterpret_cast<wchar_t *> (short_gbk),
		-1, NULL, 0, NULL, NULL);

	char *char_gbk = new char[len + 1];
	memset(char_gbk, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, reinterpret_cast<wchar_t *> (short_gbk), -1,
		char_gbk, len, NULL, NULL);

	std::string result_gbk(char_gbk);
	delete[] char_gbk;
	delete[] short_gbk;

	return result_gbk;
}

/**
* @brief httpclient::HttpGet
* @param request   请求参数
* @param response   获取结果参数
* @return
*/
int httpclient::HttpGet(const std::string& request, std::string &response)
{
	httplib::Headers headers = createCommonHeader();
	httplib::Client cli(_hostname);

	std::string wurl = "/v1/music/query?" + request;

	//windows平台转换成utf8
	string utf8s = gbk_to_utf8(wurl);

	auto res = cli.Get(utf8s.c_str(), headers);
	if (res && res->status == 200){
		response = res->body;
		return 0;
	}
	return -1;
}

/*
| 名称             | 类型     | 必填   | 说明                                       |
| appId     | String   | 是       | AIUI开放平台的应用appid = 6012b116                                       |
| token     | String   | 是       | token有效期五分钟。token的生成规则：将appId、appKey和timestamp进行字符串拼接，然后md5加密。md5(appId+appKey+timestamp)。appKey可以在AIUI开放平台“我的应用”下查询。 md5sum(6012b1164759acceaf738d7aa979836171a08770 1611844887965) |
| timestamp | Long     | 是       | 13位时间戳                                                   |
| deviceId  | String   | 是       | 设备id   |  随意  例如1234
*/
std::ostringstream httpclient::generateRequset()
{
	int64_t _stamp = getTimeStamp();
	string _token = token(_stamp);
	cout << "_stamp=" << _stamp << "token = " << _token;
	ostringstream request;
	request << "timestamp=" << std::to_string(_stamp);
	request << "&appId=" << appid;
	request << "&token=" << _token;
	request << "&deviceId=" << "1234";
	return request;
}

/**
* @brief 创建http通用头部信息
* @return   头部信息
*/
httplib::Headers httpclient::createCommonHeader()
{
	httplib::Headers headers = {
		{ "Content-Type", "application/json; charset=utf-8" },
		{ "x-requested-with", "XMLHttpRequest" },
	};
	return headers;
}

/**
* @brief 通过性别获取歌手名
* @param gender  性别名称
*/
int httpclient::HttpGetArtistByGender(const string &gender, char **out, int *len)
{
	std::ostringstream request = generateRequset();
	request << "&gender=" << gender;

	std::string result;
	int res = HttpGet(request.str(), result);
	if (res == 0) {
		std::string gbkout = utf8_to_gbk(result);
		*out = strdup(gbkout.c_str());
		*len = gbkout.length();
		cout << gbkout << endl;
		return 0;
	}
	return -1;
}

inline std::string getCategory(AIUI_MUSIC_CATEGORY_TYPE __type) {
	std::string __requ;
	switch (__type) {
	case AIUI_MUSIC_CATEGORY_GENDER:
		__requ = "&gender=";
		break;
	case AIUI_MUSIC_CATEGORY_GENRE:
		__requ = "&genre=";
		break;
	case AIUI_MUSIC_CATEGORY_AREA:
		__requ = "&area=";
		break;
	case AIUI_MUSIC_CATEGORY_LANG:
		__requ = "&lang=";
		break;
	default:
		break;
	}
	return std::move(__requ);
}

/**
* @brief 通过歌手名获取歌曲名称
* @param 歌手名称
*/
/**
* @brief HttpGetSongByArtist
* @param __type 分类
* @param __type_val 类型值
* @param __artist 歌手名
* @return
*/
int httpclient::HttpGetSongByArtist(AIUI_MUSIC_CATEGORY_TYPE __type, const std::string& __type_val, const std::string &__artist, char **out, int *len){
	std::ostringstream request = generateRequset();

	request << "&artist=" << __artist;
	request << getCategory(__type) << __type_val;

	std::string result;
	int res = HttpGet(request.str(), result);
	if (res == 0) {
		std::string gbkout = utf8_to_gbk(result);
		*out = strdup(gbkout.c_str());
		*len = gbkout.length();
		cout << gbkout << endl;
		return 0;
	}
	return -1;
}


/**
* @brief httpclient::HttpGetMicBySong  通过歌曲名称获取播放地址
* @param __type  分类
* @param __type_val 分类值
* @param __artist 歌手名
* @param __song   歌曲名称
* @return
*/
int httpclient::HttpGetMicBySong(AIUI_MUSIC_CATEGORY_TYPE __type, const std::string& __type_val, const std::string& __artist, const std::string &__song, char **out, int *len)
{
	std::ostringstream request = generateRequset();
	request << "&song=" << __song;
	request << getCategory(__type) << __type_val;
	request << "&artist=" << __artist;

	std::string result;
	int res = HttpGet(request.str(), result);
	if (res == 0) {
		std::string gbkout = utf8_to_gbk(result);
		*out = strdup(gbkout.c_str());
		*len = gbkout.length();
		cout << gbkout << endl;
		return 0;
	}
	return -1;
}

/**
* @brief httpclient::HttpGetArtistByGenre   通过流派获取歌手名
* @param genre   流派
*/
int httpclient::HttpGetArtistByGenre(const std::string &genre, char **out, int *len)
{
	std::ostringstream request = generateRequset();
	request << "&genre=" << genre;

	std::string result;
	int res = HttpGet(request.str(), result);
	if (res == 0) {
		std::string gbkout = utf8_to_gbk(result);
		*out = strdup(gbkout.c_str());
		*len = gbkout.length();
		cout << gbkout << endl;
		return 0;
	}
	return -1;
}

/**
* @brief httpclient::HttpGetArtistByArea   通过区域获取歌手名
* @param area   区域
* @return
*/
int httpclient::HttpGetArtistByArea(const string &area, char **out, int *len)
{
	std::ostringstream request = generateRequset();
	request << "&area=" << area;

	std::string result;
	int res = HttpGet(request.str(), result);
	if (res == 0) {
		std::string gbkout = utf8_to_gbk(result);
		*out = strdup(gbkout.c_str());
		*len = gbkout.length();
		cout << gbkout << endl;
		return 0;
	}
	return -1;
}

/**
* @brief httpclient::HttpGetArtistByLanguage   通过语言获取歌手名
* @param lang 语言
* @return
*/
int httpclient::HttpGetArtistByLanguage(const string &lang, char **out, int *len)
{
	std::ostringstream request = generateRequset();
	request << "&lang=" << lang;

	std::string result;
	int res = HttpGet(request.str(), result);
	if (res == 0) {
		std::string gbkout = utf8_to_gbk(result);
		*out = strdup(gbkout.c_str());
		*len = gbkout.length();
		cout << gbkout << endl;
		return 0;
	}
	return -1;
}

/**
* @brief httpclient::parse  解析aiuiresult结果
* @param aiuiJson   aiui结果
* @return
*/
AiuiResult* httpclient::parse(const std::string& aiuiJson)
{
	if (aiuiJson.empty()){
		return nullptr;
	}
	picojson::value v;
	std::string err = picojson::parse(v, aiuiJson);
	if (!err.empty()){
		cout << err << endl;
		return nullptr;
	}

	if (!v.is<picojson::object>()){
		return nullptr;
	}

	AiuiResult *aiuiresult = new AiuiResult;
	aiuiresult->Rc = v.get("rc").get<string>();
	aiuiresult->Msg = v.get("msg").get<string>();
	aiuiresult->Offset = v.get("offset").get<string>();
	aiuiresult->Limit = v.get("limit").get<string>();
	aiuiresult->Sid = v.get("sid").get<string>();
	aiuiresult->Total = v.get("total").get<string>();

	if (aiuiresult->Rc == "0") {
		auto _result = v.get("result");
		if (_result.is<picojson::array>()) {
			picojson::array list = _result.get<picojson::array>();
			for (picojson::array::iterator iter = list.begin(); iter != list.end(); ++iter) {
				Result cres;
				if ((*iter).contains("songname"))
					cres.Songname = (*iter).get("songname").get<string>();

				if ((*iter).contains("audiopath"))
					cres.Audiopath = (*iter).get("audiopath").get<string>();
				if ((*iter).contains("singernames")) {
					if ((*iter).get("singernames").is<picojson::array>()){
						picojson::array singers = (*iter).get("singernames").get<picojson::array>();
						for (picojson::array::iterator siter = singers.begin(); siter != singers.end(); ++siter) {
							string sing;
							sing = (*siter).get<string>();
							cres.Singernames.push_back(sing);
						}
					}
				}
				aiuiresult->result.push_back(cres);
			}
		}
	}
	return aiuiresult;
}
