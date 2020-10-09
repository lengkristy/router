#include "moon_msg.h"
#include "moon_protocol.h"
#include "../module/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

	/**
	 * 函数说明：
	 *   判断在网络上获取的数据包是否是包头开始，数据报文的前8个字节为包头标识
	 * 返回值：
	 *   如果是返回true，否则返回false
	 */
	bool pkg_is_head(moon_char* pkg)
	{
		moon_char head_flag[9] = {0};
		moon_char stand_head_flag[9] = {0};
		if(pkg == NULL)
		{
			return false;
		}
		if(moon_char_length(pkg) < PKG_HEAD_LENGTH)
		{
			return false;
		}
		head_flag[0] = pkg[0];
		head_flag[1] = pkg[1];
		head_flag[2] = pkg[2];
		head_flag[3] = pkg[3];
		head_flag[4] = pkg[4];
		head_flag[5] = pkg[5];
		head_flag[6] = pkg[6];
		head_flag[7] = pkg[7];
		char_to_moon_char(PKG_HEAD_FLAG,stand_head_flag);
		if(!moon_char_equals(head_flag,stand_head_flag))
		{
			return false;
		}
		return true;
	}

	/**
	 * @desc parse client running environment message
	 * @param msgData:message body
	 * @return if success return ClientEnvironment struct pointer,otherwise return NULL
	 **/
	bool parse_client_running_environment(moon_char* msgData,_out_ client_environment* p_client_env)
	{
		cJSON * root = NULL;
		cJSON * body = NULL;
		cJSON * item = NULL;
		char* ascii_msg;
		int msg_body_length = 0;
		int length = moon_char_length(msgData);
		int size = (length + 1) * MOON_CHAR_SIZE;//
		ascii_msg = (moon_char*)moon_malloc(size);
		moon_char_to_char(msgData,ascii_msg);
		root = cJSON_Parse(ascii_msg);
		if (root == NULL)
		{
			moon_free(ascii_msg);
			return false;
		}
		if (root->type == cJSON_Object)
		{
			body = cJSON_GetObjectItem(root,"message_body");
			if(body == NULL)
			{
				moon_free(ascii_msg);
				cJSON_Delete(root);
				return false;
			}
			body = cJSON_GetObjectItem(body,"content");
			if(body == NULL)
			{
				moon_free(ascii_msg);
				cJSON_Delete(root);
				return false;
			}
		
			item = cJSON_GetObjectItem(body,"client_sdk_version");
			if (item != NULL && !stringIsEmpty(item->valuestring))
			{
				char_to_moon_char(item->valuestring,p_client_env->client_sdk_version);
			}
			item = cJSON_GetObjectItem(body,"client_platform");
			if (item != NULL && !stringIsEmpty(item->valuestring))
			{
				char_to_moon_char(item->valuestring,p_client_env->client_platform);
			}
			item = cJSON_GetObjectItem(body,"opra_system_version");
			if (item != NULL && !stringIsEmpty(item->valuestring))
			{
				char_to_moon_char(item->valuestring,p_client_env->opra_system_version);
			}
			item = cJSON_GetObjectItem(body,"connect_sdk_token");
			if (item != NULL && !stringIsEmpty(item->valuestring))
			{
				char_to_moon_char(item->valuestring,p_client_env->connect_sdk_token);
			}
			item = cJSON_GetObjectItem(body,"client_id");
			if (item != NULL && !stringIsEmpty(item->valuestring))
			{
				char_to_moon_char(item->valuestring,p_client_env->client_id);
			}
		}
		moon_free(ascii_msg);
		cJSON_Delete(root);
		return true;
	}

	/**
	 * 函数说明：
	 *   解析数据包，将包头后面的数据解析出来
	 * 参数：
	 *   src_pkg：原始数据
	 *   out_data：解析后得到的业务JSON数据
	 * 返回值：
	 *   返回该包的大小
	 */
	int parse_pkg(moon_char* src_pkg,_out_ moon_char* out_data)
	{
		unsigned int pkg_size = 0;

		moon_char head_size[9] = {0};

		unsigned int index = 0;

		moon_char* p = src_pkg;

		if(src_pkg == NULL)
		{
			return 0;
		}
		if(moon_char_length(src_pkg) < PKG_HEAD_LENGTH)
		{
			return 0;
		}
		head_size[0] = src_pkg[8];
		head_size[1] = src_pkg[9];
		head_size[2] = src_pkg[10];
		head_size[3] = src_pkg[11];
	
		if(!moon_string_parse_to_int((char*)head_size,&pkg_size))
		{
			return 0;
		}
		//从第8个字节开始读取，一直读pkg_size个字节
		p = p + PKG_HEAD_LENGTH;
		for(index = 0;index < pkg_size;index++)
		{
			out_data[index] = p[index];
		}
		return pkg_size;
	}

#ifdef __cplusplus
}
#endif