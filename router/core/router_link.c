#include "router_link.h"

#ifdef __cplusplus
extern "C" {
#endif


	/*����ȫ�ֵ�·�ɱ�*/
	_global_ map *g_router_link_map;


	/**
	 * ����˵����
	 *   ��ʼ��·�ɱ�
	 */
	void init_router_link_table()
	{
		g_router_link_map = map_init();
		//��ע�����ķ����ȡ·�ɱ������
	}

#ifdef __cplusplus
}
#endif