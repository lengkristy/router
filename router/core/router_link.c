#include "router_link.h"

#ifdef __cplusplus
extern "C" {
#endif


	/*定义全局的路由表*/
	_global_ map *g_router_link_map;


	/**
	 * 函数说明：
	 *   初始化路由表
	 */
	void init_router_link_table()
	{
		g_router_link_map = map_init();
		//向注册中心发起获取路由表的请求
	}

#ifdef __cplusplus
}
#endif