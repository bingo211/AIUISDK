// IFLYSDK.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include  "ISDKDLLLoader.h"
#include "JsonParse.h"

void ProcMvsUrlCallback(const char *url, int len){
	printf_s("url = %s -- length = %d\n",url,len);
}

int _tmain(int argc, _TCHAR* argv[])
{
	IFLY_SDK_DLL_INSTANCE.loadmod(ISDKC_hook::DLL_NAME);
/*
	char *result;
	int len;
	int res = IFLY_SDK_DLL_INSTANCE.func_GetArtistByLanguage("周杰伦",&result,&len);

	printf("---------%s  -\n",result);
	AiuiResult *ares = JsonParse::parse(std::string(result,len));
	IFLY_SDK_DLL_INSTANCE.func_FreeObject(&result);

	//IFLY_SDK_DLL_INSTANCE.freemod();

	// 新闻和天气技能场景
	int ret = IFLY_SDK_DLL_INSTANCE.func_InitSession("127.0.0.1:2335",ProcMvsUrlCallback,nullptr,nullptr,nullptr,nullptr);
	if (ret){
		printf("------failed----\n");
	}
	//新闻场景
	IFLY_SDK_DLL_INSTANCE.func_MvsNewsScence("军事", "军事");
	//天气场景，参数为地址
	IFLY_SDK_DLL_INSTANCE.func_MvsWeatherScence("合肥");

    //IFLY_SDK_DLL_INSTANCE.func_DestroySession();
	
*/

	IFLY_SDK_DLL_INSTANCE.func_IFLY_PLAYER_Start("http://aiui.storage.iflyresearch.com/ctimusic/128/2016-05-21/%E6%9D%8E%E5%A8%9C/%E9%9D%92%E8%97%8F%E9%AB%98%E5%8E%9F/%E5%A5%BD%E4%BA%BA%E4%B8%80%E7%94%9F%E5%B9%B3%E5%AE%891463797280.mp3");

	

	getchar();

	return 0;
}

