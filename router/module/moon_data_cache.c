#include "moon_data_cache.h"

#ifdef __cplusplus
extern "C" {
#endif

	/**
	 * ����·�ɽڵ��б�
	 * key:·�ɽڵ�id
	 * value:router_nodeָ��
	 */
	map *p_router_nodes_map = NULL;

	/**
	 * ���·�ɱ���ʾ�ӵ�ǰ·�ɵ���ÿһ��·�ɵ�·�������router_link�ṹָ��
	 */
	Array_List *p_router_links = NULL;


	/**
	 * ����˵����
	 *   ��ʼ������
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
	 * ����˵����
	 *    �ͷŻ���
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
	 * ����˵����
	 *   ������·�ɽڵ���Ϣ�����û�������ӣ�����������
	 * ����˵����
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
			map_remove(p_router_nodes_map,p_router_node);
		}
		//Ȼ�����
		map_put(p_router_nodes_map,p_router_node->node_id,p_router_node);
	}

	/**
	 * ����˵����
	 *   ͨ��router�ڵ��ȡrouter��Ϣ
	 * ����ֵ��
	 *   ����router_nodeָ��
	 */
	router_node* get_router_node_by_id(char *router_id)
	{
		return (router_node*)map_get(p_router_nodes_map,router_id);
	}

	/**
	 * ����˵����
	 *   ����·�ɱ�
	 * ����˵����
	 *   p_router_link��һ��·�ɱ���ʾ�ӵ�ǰ·�ɽڵ㵽ĳһ��·�ɽڵ��·��
	 *   p_dest_router_id�������Ŀ��·�ɷ���id
	 */
	void update_router_link(router_link *p_router_link,const char *p_dest_router_id)
	{

	}

	/**
	 * ����˵����
	 *   ͨ��Ŀ��·��id��ȡ·�ɱ�
	 * ������
	 *   p_dest_router_id��Ŀ��·��id
	 * ����ֵ��
	 *   router_link������·������
	 */
	router_link* get_router_link_by_router_id(const char *p_dest_router_id)
	{
		return NULL;
	}


#ifdef __cplusplus
extern "C" {
#endif