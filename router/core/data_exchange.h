/***************************************************************************
 * �ļ�˵����
 *       ��ģ����Ҫ����ע�����Ľ������ݽ�����ͨ��http�ķ�ʽ��ȡ�����Լ��ύ����
 *
 ***************************************************************************/

#ifndef _DATA_EXCHANGE_H
#define _DATA_EXCHANGE_H

#include "../cfg/environment.h"

#ifdef __cplusplus
extern "C" {
#endif

	/**
	 * ����˵����
	 *    �������ݽ�������
	 * ����˵����
	 *    p_router_server_config����������
	 */
	void start_data_exchange_service( router_server_config *p_router_server_config );

	/**
	 * ����˵����
	 *    ֹͣ���ݽ�������
	 */
	void stop_data_exchange_service();

#ifdef __cplusplus
extern "C" {
#endif

#endif