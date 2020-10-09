#include "moon_data_cache.h"
#include "../module/moon_memory_pool.h"

#ifdef __cplusplus
extern "C" {
#endif

	/**
	 * 缓存路由节点列表
	 * key:路由节点id
	 * value:router_node指针
	 */
	map *p_router_nodes_map = NULL;

	/**
	 * 存放路由表，表示从当前路由到达每一条路由的路径：存放router_link结构指针
	 */
	Array_List *p_router_links = NULL;


	/**
	 * 函数说明：
	 *   初始化缓存
	 */
	void init_cache()
	{
		if (p_router_nodes_map == NULL)
		{
			p_router_nodes_map = map_init();
		}

		if (p_router_links == NULL)
		{
			p_router_links = array_list_init();
		}
	}

	/**
	 * 函数说明：
	 *    释放缓存
	 */
	void free_cache()
	{
		if (p_router_nodes_map != NULL)
		{
			map_free(p_router_nodes_map);
		}

		if (p_router_links != NULL)
		{
			array_list_free(p_router_links);
		}
	}


	/**
	 * 函数说明：
	 *   更更新路由节点信息，如果没有则增加，如果有则更新
	 * 参数说明：
	 *   p_router_node
	 */
	void update_router_node(router_node *p_router_node)
	{
		router_node* p_node = NULL;
		if (p_router_node == NULL)
		{
			return;
		}
		p_node = (router_node*)map_get(p_router_nodes_map,p_router_node->node_id);
		if (p_node != NULL)
		{
			moon_free(p_node);
			map_remove(p_router_nodes_map,p_router_node->node_id);
		}
		//然后插入
		map_put(p_router_nodes_map,p_router_node->node_id,p_router_node);
	}

	/**
	 * 函数说明：
	 *   通过router节点获取router信息
	 * 返回值：
	 *   返回router_node指针
	 */
	router_node* get_router_node_by_id(char *router_id)
	{
		return (router_node*)map_get(p_router_nodes_map,router_id);
	}

	/**
	 * 函数说明：
	 *   更新路由表
	 * 参数说明：
	 *   p_router_link：一条路由表，表示从当前路由节点到某一个路由节点的路径
	 *   p_dest_router_id：到达的目标路由服务id
	 */
	void update_router_link(router_link *p_router_link,const char *p_dest_router_id)
	{

	}

	/**
	 * 函数说明：
	 *   通过目标路由id获取路由表
	 * 参数：
	 *   p_dest_router_id：目标路由id
	 * 返回值：
	 *   router_link：返回路有链表
	 */
	router_link* get_router_link_by_router_id(const char *p_dest_router_id)
	{
		return NULL;
	}


#ifdef __cplusplus
}
#endif