#pragma once

#ifdef WIN32_DLL_EXPORTS
#define WIN32_DLL_API __declspec(dllexport) 
#else
#define WIN32_DLL_API __declspec(dllimport) 
#endif

WIN32_DLL_API LRESULT CALLBACK MyHookProc(int, WPARAM, LPARAM);
WIN32_DLL_API int SetHook(HWND hOwnerWnd);
WIN32_DLL_API int ResetHook();
