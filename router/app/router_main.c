#include "router_main.h"

#ifdef __cplusplus
extern "C" {
#endif


	/**window main entry point*/
#ifdef MS_WINDOWS
	int windows_main(int argc, _TCHAR* argv[])
	{
		router_start();
		return 0;
	}
#endif


	/**linux main entry point*/
#ifdef LINUX
	int linux_main(int argc, char **argv)
	{
		return 0;
	}
#endif

#ifdef __cplusplus
}
#endif