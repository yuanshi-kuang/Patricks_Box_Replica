#pragma once
#include <Windows.h>
#include <string>
using namespace std;
inline void TopMessage(const wstring& title, const wstring& message)
{
	HANDLE hThread = CreateThread
	(
		NULL,
		0,
		[](LPVOID param) -> DWORD
		{
			auto data = (pair<wstring, wstring>*)param;
			MessageBoxW(NULL, data->second.c_str(), data->first.c_str(), MB_OK | MB_ICONINFORMATION);
			delete data;
			return 0;
		},
		new pair<wstring, wstring>(title, message),
		0,
		NULL
	);
	Sleep(50);
	if (HWND hWnd = FindWindowW(NULL, title.c_str())) { SetForegroundWindow(hWnd); }
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
}