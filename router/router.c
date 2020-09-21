#include "cfg/environment.h"
#include "app/router_main.h"
#include "module/moon_http_client.h"

#ifdef MS_WINDOWS
#include <windows.h>
#include <tchar.h>
#pragma comment (lib,"User32.lib")
#endif

#ifdef MS_WINDOWS
int main(int argc, _TCHAR* argv[])
{
	//http_response * p_response = http_do_post("http://192.168.2.227:8088/zzjg-service/api/org/unit/getUnitTree",NULL,"{\"dwbm\":\"100000\",\"sfzsbm\":false,\"sfzsjs\":false,\"sfzslsbm\":false,\"sfzsry\":false,\"sfzsxjdw\":true}");
	//if (p_response != NULL)
	//{
	//	http_response_free(p_response);
	//	p_response = NULL;
	//}
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