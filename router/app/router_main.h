#ifndef _ROUTER_MAIN_H
#define _ROUTER_MAIN_H

#include "../cfg/environment.h"
#ifdef MS_WINDOWS
#include <tchar.h>
#pragma comment (lib,"User32.lib")
#endif

#ifdef __cplusplus
extern "C" {
#endif

	/**window main entry point*/
#ifdef MS_WINDOWS
	int windows_main(int argc, _TCHAR* argv[]);//windows MoonÈë¿Ú
#endif


	/**linux main entry point*/
#ifdef LINUX
	int linux_main(int argc, char **argv);
#endif


#ifdef __cplusplus
}
#endif
#endif