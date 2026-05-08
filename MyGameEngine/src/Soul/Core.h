#pragma once

#ifdef SL_PLATFORM_WINDOWS
	#ifdef SL_BUILD_DLL
		#define SOUL_API __declspec(dllexport)
	#else
		#define SOUL_API __declspec(dllimport)
	#endif // SL_BUILD_DLL
#else 
	#error Soul only supports Windows! 
#endif // SL_PLATFORM_WINDOWS