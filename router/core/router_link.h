/*************************************************************************
 * �ļ�˵����
 *   ���ļ�������·����·�ϵ����Ԫ���ݵĶ���
 * ����ʱ�䣺
 *   2020-09-16 14:45
 * �����ˣ�
 *   ����Ȼ
 *************************************************************************/

#ifndef _ROUTER_LINK
#define _ROUTER_LINK

#include "../collection/map.h"
#include "../module/moon_base.h"


#ifdef __cplusplus
extern "C" {
#endif

	/**
	 * ����·�ɽڵ���Ϣ
	 */
	typedef struct _router_node{
		/*�ڵ�id���ڵ�id��·�ɷ�����������ʱ������*/
		moon_char node_id[32];
		/*�ڵ����ƣ����ⲿ���ã����ܳ���255���ֽ�*/
		moon_char node_name[255];
		/*�ڵ�ip*/
		moon_char node_ip[20];
		/*�ڵ㿪�Ŷ˿�*/
		unsigned int node_port;
		/*·��״̬��0��ֹͣ��1���������У�2��������*/
		unsigned char status;
	}router_node;

	/**
	 * ·����·��Ϣ
	 */
	typedef struct _router_link{
	   /*��ǰ�ڵ�*/
	   router_node *p_current_node;
	   /*��һ���ڵ�*/
	   router_node *p_next_node;
	} router_link;

	
	/**
	 * ����˵����
	 *   ��ʼ��·�ɱ�
	 */
	void init_router_link_table();

#ifdef __cplusplus
}
#endif
#endif