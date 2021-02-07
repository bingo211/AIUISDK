#ifndef MUSIC_DLL_INCLUDE__
#define MUSIC_DLL_INCLUDE__
#include "util.h"

#if defined _WIN32
#define DLLDEP_API __stdcall
#endif

#ifdef __cplusplus
extern "C" {
#endif
#pragma region 音乐场景

	int DLLDEP_API  GetArtistByGender(const char* gender,char **out,int *len);
	typedef int (DLLDEP_API *Proc_GetArtistByGender)(const char* gender, char **out, int *len);

	int	DLLDEP_API GetSongByArtist(AIUI_MUSIC_CATEGORY_TYPE __type, const char* __type_val, const char* __artist, char **out, int *len);
	typedef int (DLLDEP_API *Proc_GetSongByArtist)(AIUI_MUSIC_CATEGORY_TYPE __type, const char* __type_val, const char* __artist, char **out, int *len);

	int DLLDEP_API GetMicBySong(AIUI_MUSIC_CATEGORY_TYPE __type, const char* __type_val, const char* __artist, const char* __song, char **out, int *len);
	typedef int(DLLDEP_API *Proc_GetMicBySong)(AIUI_MUSIC_CATEGORY_TYPE __type, const char* __type_val, const char* __artist, const char* __song, char **out, int *len);

	int DLLDEP_API GetArtistByGenre(const char* genre, char **out, int *len);
	typedef int(DLLDEP_API *Proc_GetArtistByGenre)(const char* genre, char **out, int *len);

	int DLLDEP_API GetArtistByArea(const char* area, char **out, int *len);
	typedef int(DLLDEP_API *Proc_GetArtistByArea)(const char* area, char **out, int *len);

	int DLLDEP_API GetArtistByLanguage(const char* lang, char **out, int *len);
	typedef int (DLLDEP_API *Proc_GetArtistByLanguage)(const char* lang, char **out, int *len);

	int DLLDEP_API FreeObject(char **object);
	typedef int (DLLDEP_API *Proc_FreeObject)(char **object);
#pragma endregion

#pragma region 新闻和天气场景
	int DLLDEP_API  InitSession(const char* mvs_ip, 
		                        Proc_MvsUrlCallback callback,
								const char* skills, 
								const char *appid,
								const char *appkey,
								const char *authid);

	typedef int (DLLDEP_API *Proc_InitSession)(const char* mvs_ip,
											   Proc_MvsUrlCallback callback,
											   const char* skills, 
											   const char *appid, 
											   const char *appkey, 
											   const char *authid);
	
	//天气场景
	int DLLDEP_API  MvsWeatherScence(const char *city);
	typedef int (DLLDEP_API *Proc_MvsWeatherScence)(const char *city);

	//新闻场景
	int DLLDEP_API  MvsNewsScence(const char *tags, const char *category);
	typedef int (DLLDEP_API *Proc_MvsNewsScence)(const char *tags, const char *category);


	int DLLDEP_API  DestroySession();
	typedef int (DLLDEP_API *Proc_DestroySession)();

#pragma endregion

#pragma region 播放器
	//播放器开始
	int DLLDEP_API IFLY_PLAYER_Start(const char *url);
	typedef int(DLLDEP_API *Proc_IFLY_PLAYER_Start)(const char *url);
	//播放器销毁
	int DLLDEP_API IFLY_PLAYER_Destroy();
	typedef int(DLLDEP_API *Proc_IFLY_PLAYER_Destroy)();

	//播放器暂停/继续
	int DLLDEP_API IFLY_PLAYER_Pause();
	typedef int(DLLDEP_API *Proc_IFLY_PLAYER_Pause)();
#pragma endregion 

#ifdef __cplusplus
}
#endif

#endif