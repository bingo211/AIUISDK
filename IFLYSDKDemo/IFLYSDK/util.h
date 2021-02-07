#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>
using namespace  std;

typedef struct __Result {
	std::vector<std::string> Movienames;
	string Programname;
	string Source;
	std::vector<string> Tagnames;
	string Pictures;
	string Songname;
	std::vector<string> Singeraliasnames;

	string Albumname;
	string Itemid;
	vector<string> Singerids;
	int Publishtime;
	vector<string> Singernames;
	vector<string> Neatsongname;
	string Audiopath;
}Result;

typedef struct __AiuiResult{
	std::string Limit;
	std::string Msg;
	string Offset;
	string  Rc;
	std::vector<Result> result;
	std::vector<string> Semantic;
	string Sid;
	string Total;
}AiuiResult;

/**
{
"sid":"11111",
"code":0,
"dataType":"connection",
"data":{
"httpUrl":"http://172.31.97.139:18080/live/11111.flv",
"httpsUrl":"https://172.31.97.139:18088/live/11111.flv",
"rtcUrl":"webrtc://172.31.97.139:11985/live/11111",
"rtcsUrl":"webrtc://172.31.97.139:11990/live/11111",
"rtmpUrl":"rtmp://172.31.97.139:11935/live/11111"
}
}
**/
typedef  struct _mvsResult {
	std::string sid;
	int code;
	std::string dataType;
	struct data{
		std::string rtmpUrl;
		std::string httpUrl;
		std::string httpsUrl;
		std::string rtcUrl;
		std::string rtcsUrl;
	}d;
}mvsResult;

enum AIUI_MUSIC_CATEGORY_TYPE {
	AIUI_MUSIC_CATEGORY_GENDER = 0,
	AIUI_MUSIC_CATEGORY_GENRE,
	AIUI_MUSIC_CATEGORY_AREA,
	AIUI_MUSIC_CATEGORY_LANG,
};

typedef void (*Proc_MvsUrlCallback)(const char *url, int len);

#endif // UTIL_H
