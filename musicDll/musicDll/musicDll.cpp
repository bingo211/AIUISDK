// musicDll.cpp : Defines the exported functions for the DLL application.
//
#include "musicDll.h"
#include "httpclient.h"
#include  "aiuimgr.h"

int	DLLDEP_API GetArtistByGender(const char* gender, char **out, int *len)
{
	httpclient client;
	return client.HttpGetArtistByGender(gender,out,len);
}

int DLLDEP_API  GetSongByArtist(AIUI_MUSIC_CATEGORY_TYPE __type, const char* __type_val, const char* __artist, char **out, int *len)
{
	httpclient client;
	return client.HttpGetSongByArtist(__type, __type_val, __artist, out, len);
}

int DLLDEP_API GetMicBySong(AIUI_MUSIC_CATEGORY_TYPE __type, const char* __type_val, const char* __artist, const char* __song, char **out, int *len)
{
	httpclient client;
	return client.HttpGetMicBySong(__type, __type_val, __artist, __song, out, len);
}

int DLLDEP_API GetArtistByGenre(const char* genre, char **out, int *len)
{
	httpclient client;
	return client.HttpGetArtistByGenre(genre, out, len);
}

int DLLDEP_API GetArtistByArea(const char* area, char **out, int *len)
{
	httpclient client;
	return client.HttpGetArtistByArea(area, out, len);
}

int  DLLDEP_API GetArtistByLanguage(const char* lang, char **out, int *len)
{
	httpclient client;
	return client.HttpGetArtistByLanguage(lang, out, len);
}

int DLLDEP_API FreeObject(char **object)
{
	if (*object)
	{
		free(*object);
		*object = nullptr;
	}
	return 0;
}

int DLLDEP_API  InitSession(const char* mvs_ip,
	Proc_MvsUrlCallback callback,
	const char* skills,
	const char *appid,
	const char *appkey,
	const char *authid)
{
	if (callback == nullptr || mvs_ip == nullptr) {
		return -1;
	}

	if (skills && appid && appkey && authid){
		return aiuiMgr::instance()->init_session(mvs_ip, callback, skills, appid, appkey, authid);
	}
	else{
		return aiuiMgr::instance()->init_session(mvs_ip,callback);
	}
}

int DLLDEP_API  DestroySession()
{
	aiuiMgr::instance()->stop_session();
	return 0;
}

int DLLDEP_API  MvsWeatherScence(const char *city)
{
	aiuiMgr::instance()->mvs_weather_scence(city);
	return 0;
}

int DLLDEP_API  MvsNewsScence(const char *tags, const char *category)
{
	aiuiMgr::instance()->mvs_news_scence(tags, category);
	return 0;
}

#include "CAIUIPlayer.h"

int DLLDEP_API IFLY_PLAYER_Start(const char *url)
{
	AIUIPlayer_play(url);
	return 0;
}
//²¥·ÅÆ÷Ïú»Ù
int DLLDEP_API IFLY_PLAYER_Destroy()
{
	AIUIPlayer_destroy();
	return 0;
}

//²¥·ÅÆ÷ÔÝÍ£/¼ÌÐø
int DLLDEP_API IFLY_PLAYER_Pause()
{
	AIUIPlayer_pause();
	return 0;
}