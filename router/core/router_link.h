/*************************************************************************
 * 文件说明：
 *   该文件定义了路由链路上的相关元数据的定义
 * 创建时间：
 *   2020-09-16 14:45
 * 创建人：
 *   代浩然
 *************************************************************************/

#ifndef _ROUTER_LINK
#define _ROUTER_LINK

#include "../collection/map.h"
#include "../module/moon_base.h"


#ifdef __cplusplus
extern "C" {
#endif

	/**
	 * 定义路由节点信息
	 */
	typedef struct _router_node{
		/*节点id，节点id在路由服务器启动的时候生成*/
		moon_char node_id[32];
		/*节点名称，有外部配置，不能超过255个字节*/
		moon_char node_name[255];
		/*节点ip*/
		moon_char node_ip[20];
		/*节点开放端口*/
		unsigned int node_port;
		/*路由状态：0：停止；1：正常运行；2：满负载*/
		unsigned char status;
	}router_node;

	/**
	 * 路由链路信息
	 */
	typedef struct _router_link{
	   /*当前节点*/
	   router_node *p_current_node;
	   /*下一个节点*/
	   router_node *p_next_node;
	} router_link;

	
	/**
	 * 函数说明：
	 *   初始化路由表
	 */
	void init_router_link_table();

#ifdef __cplusplus
}
#endif
#endif