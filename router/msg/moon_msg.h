/*******************************************************************************************************************
 *  ��ģ��Ϊ��Ϣ����ģ��    
 *  �����ˣ�����Ȼ
 *  ����ʱ�䣺2020-10-09
 *******************************************************************************************************************/
#ifndef _MOON_MSG_H
#define _MOON_MSG_H
#endif

#include "../cfg/environment.h"
#include "../module/moon_base.h"
#include "../core/moon_session.h"

#ifdef __cplusplus
extern "C" {
#endif

	/**
	 * ����˵����
	 *   �ж��������ϻ�ȡ�����ݰ��Ƿ��ǰ�ͷ��ʼ�����ݱ��ĵ�ǰ8���ֽ�Ϊ��ͷ��ʶ
	 * ����ֵ��
	 *   ����Ƿ���true�����򷵻�false
	 */
	bool pkg_is_head(moon_char* pkg);

	/**
	 * @desc parse client running environment message
	 * @param msgData:message body
	 * @return if success return ClientEnvironment struct pointer,otherwise return NULL
	 **/
	bool parse_client_running_environment(moon_char* msgData,_out_ client_environment* p_client_env);

	/**
	 * ����˵����
	 *   �������ݰ�������ͷ��������ݽ�������
	 * ������
	 *   src_pkg��ԭʼ����
	 *   out_data��������õ���ҵ��JSON����
	 * ����ֵ��
	 *   ���ظð��Ĵ�С
	 */
	int parse_pkg(moon_char* src_pkg,_out_ moon_char* out_data);

#ifdef __cplusplus
}
#endif