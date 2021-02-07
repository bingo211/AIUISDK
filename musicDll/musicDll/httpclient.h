#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H
#include <string>
#include <sstream>
#include "util.h"
#include "httplib.h"

const static std::string appid = "6012b116";
const static std::string appkey = "4759acceaf738d7aa979836171a08770";
const static std::string _url = "http://content.xfyun.cn/v1/music/query";
const static std::string _hostname = "content.xfyun.cn";


//复写http  get请求
class httpclient {
public:
   httpclient() = default;
   ~httpclient() = default;

   //性别获取歌手名
   int HttpGetArtistByGender(const std::string &gender, char **out, int *len);

   //通过歌手名获取歌曲
   int HttpGetSongByArtist(AIUI_MUSIC_CATEGORY_TYPE __type, const std::string& __type_val, const std::string &__artist, char **out, int *len);
   //通过歌曲获取音乐播放url
   int HttpGetMicBySong(AIUI_MUSIC_CATEGORY_TYPE __type, const std::string& __type_val, const std::string& __artist, const std::string &__song, char **out, int *len);

   //通过流派获取歌手名
   int HttpGetArtistByGenre(const std::string &genre, char **out, int *len);

   //通过地域获取歌手名
   int HttpGetArtistByArea(const std::string &area, char **out, int *len);

   //通过语言获取歌手名
   int HttpGetArtistByLanguage(const std::string &lang, char **out, int *len);

public:
   httplib::Headers createCommonHeader();
   int HttpGet(const std::string& request, std::string &response);
   std::ostringstream generateRequset();
   AiuiResult* parse(const std::string& aiuiJson);
};


#endif // HTTPCLIENT_H
