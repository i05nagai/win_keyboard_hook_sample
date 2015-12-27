// dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include "stdafx.h"
#include "Win32_dll.h"
#include <string>
#include <tchar.h>

HHOOK hMyHook = 0;
HINSTANCE hInst;
HWND hOwner;

void SendKeys();

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
        hInst = hModule;
        break;
	case DLL_THREAD_ATTACH:
        hInst = hModule;
        break;
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}



WIN32_DLL_API int  SetHook(HWND hOwnerWnd)
{
    hOwner = hOwnerWnd;

    hMyHook = SetWindowsHookEx(WH_KEYBOARD, MyHookProc, hInst, 0);
    if (hMyHook == NULL) {
        MessageBox(hOwner, TEXT("fail to hook event."), TEXT("dll"), MB_OK);
    }
    return 0;
}

WIN32_DLL_API int ResetHook()
{
    if (UnhookWindowsHookEx(hMyHook) == 0) {
        MessageBox(hOwner, TEXT("fail to un-hook event."), TEXT("Error"), MB_OK);
    }
    return 0;
}

WIN32_DLL_API LRESULT CALLBACK MyHookProc(int nCode, WPARAM wp, LPARAM lp)
{
    if (nCode < 0) {
        return CallNextHookEx(hMyHook, nCode, wp, lp);
    }

    //get pressed key name.
    TCHAR lpszName[256];
    GetKeyNameText(lp, lpszName, 0xFF);
    
    if (_tcscmp(lpszName, _T("Caps Lock")) == 0) {
        //MessageBeep(0xffffffff);
        SendKeys();
        return true;
    }

    return CallNextHookEx(hMyHook, nCode, wp, lp);
}

void SendKeys()
{
    INPUT input[1];
    memset(input, 0, sizeof(INPUT) * 1);
    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = VK_ESCAPE;
    //input[0].ki.dwFlags = KEYEVENTF_KEYUP; if set this flag, key up. otherwise key press.
    //input[1].type = INPUT_KEYBOARD;
    //input[1].ki.wVk = VK_CONTROL;
    //input[1].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, input, sizeof(INPUT));
}
