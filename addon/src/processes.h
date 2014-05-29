
#pragma once

#include "stdafx.h"
#include "globaldata.h"

void DoIncrementalMouseMove(int aX1, int aY1, int aX2, int aY2, int aSpeed);
DWORD ProcessExist9x2000(LPTSTR aProcess);
#ifdef CONFIG_WINNT4
DWORD ProcessExistNT4(LPTSTR aProcess);
#endif

inline DWORD ProcessExist(LPTSTR aProcess)
{
	return 
#ifdef CONFIG_WINNT4
		g_os.IsWinNT4() ? ProcessExistNT4(aProcess) :
#endif
		ProcessExist9x2000(aProcess);
}

DWORD GetProcessName(DWORD aProcessID, LPTSTR aBuf, DWORD aBufSize, bool aGetNameOnly);

bool Util_Shutdown(int nFlag);
bool Util_ShutdownHandler(HWND hwnd, DWORD lParam);
void Util_WinKill(HWND hWnd);
