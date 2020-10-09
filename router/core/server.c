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

	//ȫ������
	_global_ router_server_config* p_router_server_config;

	//���������Ƿ�������
	_global_ bool b_config_load_finish;

	/**
	* ����˵����
	*   ����·�ɷ���
	*/
	void router_start()
	{
		//��ʼ����־
		//init log
		if(!moon_log_init())
		{
			moon_write_error_log("open log file faild,server has exit.");
			return;
		}
		//��������
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

		//�������ݽ�����������ע������

		//����ͨ�ŷ���
#ifdef MS_WINDOWS
		if (!ms_iocp_server_start(p_router_server_config))
		{
			moon_write_error_log("lauch iocp service failed,server exit...");
			router_stop();
			return;
		}
		
#endif

		//�ȴ��û���������
		process_command();
	}

	/**
	 * ����˵����
	 *   ֹͣ·�ɷ���
	 */
	void router_stop()
	{
		
#ifdef MS_WINDOWS
		ms_iocp_server_stop();
#endif
		//close log
		moon_log_close();

		//�ͷų�ʼ�����ڴ�
		moon_free(p_router_server_config);

	}

#ifdef __cplusplus
	extern "C" {
#endif