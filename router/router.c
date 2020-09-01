

#ifdef MS_WINDOWS
#include <windows.h>
#pragma comment (lib,"User32.lib")
#endif

#ifdef MS_WINDOWS
int _tmain(int argc, _TCHAR* argv[])
{
	HWND hWnd = GetConsoleWindow();
	SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(NULL, _T("IDI_ICON3")));//set icon
	return windows_main(argc,argv);
}
#else
int main(int argc, char **argv)
{
	//return linux_main(argc,argv);
	return 0;
}
#endif