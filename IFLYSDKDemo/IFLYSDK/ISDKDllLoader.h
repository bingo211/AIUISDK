#ifndef IFLYTEK_SDK_DLL_LOADER
#define IFLYTEK_SDK_DLL_LOADER

#include <Windows.h>
#include "util.h"
#include "musicDll.h"

namespace ISDKC_hook
{
	const static wchar_t* DLL_NAME = L"musicDLL.dll";

#define DECLARE_FUNC_MEMBER(NAME)	Proc_##NAME func_##NAME;
#define GET_FUNC_MEMBER(NAME)	func_##NAME = (Proc_##NAME)::GetProcAddress(hMod, (LPCSTR)#NAME);	\
	if ( func_##NAME == NULL )									\
			{															\
		return -1;												\
			}

	class IFLY_SDK_DLL_C_loader
	{
	private:

		IFLY_SDK_DLL_C_loader() : hMod(NULL){}
		~IFLY_SDK_DLL_C_loader()
		{
			freemod();
		}

	public:
		HMODULE	hMod;
		DECLARE_FUNC_MEMBER(GetArtistByGender)
		DECLARE_FUNC_MEMBER(GetSongByArtist)
		DECLARE_FUNC_MEMBER(GetMicBySong)
		DECLARE_FUNC_MEMBER(GetArtistByGenre)
		DECLARE_FUNC_MEMBER(GetArtistByArea)
		DECLARE_FUNC_MEMBER(GetArtistByLanguage)
		DECLARE_FUNC_MEMBER(FreeObject)

		DECLARE_FUNC_MEMBER(InitSession)
		DECLARE_FUNC_MEMBER(MvsWeatherScence)
		DECLARE_FUNC_MEMBER(MvsNewsScence)
		DECLARE_FUNC_MEMBER(DestroySession)

		//²¥·ÅÆ÷
		DECLARE_FUNC_MEMBER(IFLY_PLAYER_Start)
		DECLARE_FUNC_MEMBER(IFLY_PLAYER_Destroy)
		DECLARE_FUNC_MEMBER(IFLY_PLAYER_Pause)

	public:

		static IFLY_SDK_DLL_C_loader& instance(){
			static IFLY_SDK_DLL_C_loader loader_;
			return loader_;
		}

	public:

		int loadmod(const wchar_t* module)
		{
			hMod = ::LoadLibraryW(module);


			if (hMod == NULL)
			{
				DWORD  ret = GetLastError();
				return (int)ret;
			}

			GET_FUNC_MEMBER(GetArtistByGender)
			GET_FUNC_MEMBER(GetSongByArtist)
			GET_FUNC_MEMBER(GetMicBySong)
			GET_FUNC_MEMBER(GetArtistByGenre)
			GET_FUNC_MEMBER(GetArtistByArea)
			GET_FUNC_MEMBER(GetArtistByLanguage)
			GET_FUNC_MEMBER(FreeObject)

			GET_FUNC_MEMBER(InitSession)
			GET_FUNC_MEMBER(MvsWeatherScence)
			GET_FUNC_MEMBER(MvsNewsScence)
			GET_FUNC_MEMBER(DestroySession)

			//²¥·ÅÆ÷
			GET_FUNC_MEMBER(IFLY_PLAYER_Start)
			GET_FUNC_MEMBER(IFLY_PLAYER_Destroy)
			GET_FUNC_MEMBER(IFLY_PLAYER_Pause)

				return 0;
		}

		int freemod()
		{
			if (hMod != NULL)
			{
				::FreeLibrary(hMod);
				hMod = NULL;
			}

			return 0;
		}
	};

};	//namespace focus_hook

#define IFLY_SDK_DLL_INSTANCE ISDKC_hook::IFLY_SDK_DLL_C_loader::instance()


#endif	/* IFLYTEK_SDK_DLL_LOADER */
