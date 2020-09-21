#include "server.h"
#include "../cfg/environment.h"

#ifdef __cplusplus
extern "C" {
#endif

	//全局配置
	_global_ router_server_config* p_router_server_config;

	//定义配置是否加载完成
	_global_ bool b_config_load_finish;

	/**
	* 函数说明：
	*   启动路由服务
	*/
	void router_start()
	{

	}

	/**
	 * 函数说明：
	 *   停止路由服务
	 */
	void router_stop()
	{

	}

#ifdef __cplusplus
	extern "C" {
#endif