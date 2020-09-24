#ifndef _MOON_DATA_CACHE_H
#define _MOON_DATA_CACHE_H
#include "../collection/map.h"
#include "../collection/array_list.h"
#include "../core/router_link.h"

#ifdef __cplusplus
extern "C" {
#endif

	/**
	 * ����˵����
	 *   ��ʼ������
	 */
	void init_cache();

	/**
	 * ����˵����
	 *   ͨ��router�ڵ��ȡrouter��Ϣ
	 * ����ֵ��
	 *   ����router_nodeָ��
	 */
	router_node* get_router_node_by_id(char *router_id);

	/**
	 * ����˵����
	 *    �ͷŻ���
	 */
	void free_cache();

	/**
	 * ����˵����
	 *   ����·�ɽڵ���Ϣ�����û�������ӣ�����������
	 * ����˵����
	 *   p_router_node
	 */
	void update_router_node(router_node *p_router_node);

	/**
	 * ����˵����
	 *   ����·�ɱ�
	 * ����˵����
	 *   p_router_link��һ��·�ɱ���ʾ�ӵ�ǰ·�ɽڵ㵽ĳһ��·�ɽڵ��·����p_router_link�����һ���ڵ�ͱ�ʾ�ﵽ��Ŀ��·��
	 *   p_dest_router_id�������Ŀ��·�ɷ���id
	 */
	void update_router_link(router_link *p_router_link,const char *p_dest_router_id);

	/**
	 * ����˵����
	 *   ͨ��Ŀ��·��id��ȡ·�ɱ�
	 * ������
	 *   p_dest_router_id��Ŀ��·��id
	 * ����ֵ��
	 *   router_link������·������
	 */
	router_link* get_router_link_by_router_id(const char *p_dest_router_id);

	

#ifdef __cplusplus
extern "C" {
#endif

#endif