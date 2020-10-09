#include "server.h"
#include "../cfg/environment.h"
#include "../module/module_cfg.h"
#include "../module/module_log.h"
#include "../module/moon_memory_pool.h"
#include "../module/module_command.h"

#ifdef MS_WINDOWS
#include "../core/ms_nt__iocp.h"
#endif

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
		//初始化日志
		//init log
		if(!moon_log_init())
		{
			moon_write_error_log("open log file faild,server has exit.");
			return;
		}
		//加载配置
		moon_write_info_log("starting router server,please waiting...");
		//load config
		if(NULL == p_router_server_config)
		{
			p_router_server_config = (router_server_config*)moon_malloc(sizeof(router_server_config));
		}
		if(!load_config(p_router_server_config))
		{
			moon_write_error_log("load config error,server has exit.");
			router_stop();
			return;
		}
		b_config_load_finish = true;

		//启动数据交换服务，连接注册中心

		//启动通信服务
#ifdef MS_WINDOWS
		if (!ms_iocp_server_start(p_router_server_config))
		{
			moon_write_error_log("lauch iocp service failed,server exit...");
			router_stop();
			return;
		}
		
#endif

		//等待用户输入命令
		process_command();
	}

	/**
	 * 函数说明：
	 *   停止路由服务
	 */
	void router_stop()
	{
		
#ifdef MS_WINDOWS
		ms_iocp_server_stop();
#endif
		//close log
		moon_log_close();

		//释放初始化的内存
		moon_free(p_router_server_config);

	}

#ifdef __cplusplus
	extern "C" {
#endif