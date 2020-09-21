#ifndef _MOON_HTTP_CLIENT_H
#define _MOON_HTTP_CLIENT_H

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#pragma comment(lib, "Ws2_32.lib")
#elif _LINUX
#include <sys/socket.h>
#elif __FreeBSD__
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#else
#error Platform not suppoted.
#endif

#ifdef __cplusplus
extern "C" {
#endif

	/* Buffered I/O macros */
	#define BUFSIZ  512

	/**
	 * url struct
	 */
	typedef struct _parsed_url 
	{
		char *uri;					/* mandatory */
		char *scheme;               /* mandatory */
		char *host;                 /* mandatory */
		char *ip; 					/* mandatory */
		char *port;                 /* optional */
		char *path;                 /* optional */
		char *query;                /* optional */
		char *fragment;             /* optional */
		char *username;             /* optional */
		char *password;             /* optional */
	} parsed_url,*p_parsed_url;

	/*
	 *	HTTP html response struct
	 */
	typedef struct _http_response
	{
		parsed_url *request_uri;/*解析的url结构*/
		char *body;/*响应的数据体*/
		char *status_code;/*字符串格式状态码*/
		int status_code_int;/*状态码*/
		long body_length;/*数据体长度*/
		char *status_text;
		char *request_headers;/*请求头*/
		char *response_headers;/*响应头*/
	}http_response;

	/**
	 * 函数说明：
	 *   发起get请求
	 * 参数：
	 *   url：请求的url地址
	 *   custom_header：自定义头部
	 *   paramName：请求的参数名称列表
	 *   paramValue：请求的参数值列表
	 *   paramCount：参数数量
	 * 返回值：
	 *   返回响应的结构体指针，使用完成之后需要调用http_response_free进行释放
	 */
	http_response* http_do_get(const char* url,const char* custom_headers,const char* paramName[],const char* paramValue[],int paramCount);

	/**
	 * 函数说明：
	 *   发起post请求
	 * 参数：
	 *   url：请求的url地址
	 *   custom_headers：自定义请求头
	 *   post_data：请求的post参数数据，请求的数据只能是JSON格式
	 * 返回值：
	 *   返回响应的结构体指针，使用完成之后需要调用http_response_free进行释放
	 */
	http_response* http_do_post(const char* url,const char* custom_headers,const char *post_data);


	/**
	 * 函数说明：
	 *   释放响应结构的内存
	 * 参数：
	 *   p_http_response：响应结构指针
	 */
	void http_response_free(http_response* p_http_response);

#ifdef __cplusplus
}
#endif

#endif