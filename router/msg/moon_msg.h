/*******************************************************************************************************************
 *  该模块为消息解析模块    
 *  创建人：代浩然
 *  创建时间：2020-10-09
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
	 * 函数说明：
	 *   判断在网络上获取的数据包是否是包头开始，数据报文的前8个字节为包头标识
	 * 返回值：
	 *   如果是返回true，否则返回false
	 */
	bool pkg_is_head(moon_char* pkg);

	/**
	 * @desc parse client running environment message
	 * @param msgData:message body
	 * @return if success return ClientEnvironment struct pointer,otherwise return NULL
	 **/
	bool parse_client_running_environment(moon_char* msgData,_out_ client_environment* p_client_env);

	/**
	 * 函数说明：
	 *   解析数据包，将包头后面的数据解析出来
	 * 参数：
	 *   src_pkg：原始数据
	 *   out_data：解析后得到的业务JSON数据
	 * 返回值：
	 *   返回该包的大小
	 */
	int parse_pkg(moon_char* src_pkg,_out_ moon_char* out_data);

#ifdef __cplusplus
}
#endif