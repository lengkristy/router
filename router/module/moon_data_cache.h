#ifndef _MOON_DATA_CACHE_H
#define _MOON_DATA_CACHE_H
#include "../collection/map.h"
#include "../collection/array_list.h"
#include "../core/router_link.h"

#ifdef __cplusplus
extern "C" {
#endif

	/**
	 * 函数说明：
	 *   初始化缓存
	 */
	void init_cache();

	/**
	 * 函数说明：
	 *   通过router节点获取router信息
	 * 返回值：
	 *   返回router_node指针
	 */
	router_node* get_router_node_by_id(char *router_id);

	/**
	 * 函数说明：
	 *    释放缓存
	 */
	void free_cache();

	/**
	 * 函数说明：
	 *   更新路由节点信息，如果没有则增加，如果有则更新
	 * 参数说明：
	 *   p_router_node
	 */
	void update_router_node(router_node *p_router_node);

	/**
	 * 函数说明：
	 *   更新路由表
	 * 参数说明：
	 *   p_router_link：一条路由表，表示从当前路由节点到某一个路由节点的路径，p_router_link的最后一个节点就表示达到的目标路由
	 *   p_dest_router_id：到达的目标路由服务id
	 */
	void update_router_link(router_link *p_router_link,const char *p_dest_router_id);

	/**
	 * 函数说明：
	 *   通过目标路由id获取路由表
	 * 参数：
	 *   p_dest_router_id：目标路由id
	 * 返回值：
	 *   router_link：返回路有链表
	 */
	router_link* get_router_link_by_router_id(const char *p_dest_router_id);

	

#ifdef __cplusplus
extern "C" {
#endif

#endif