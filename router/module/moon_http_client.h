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
		parsed_url *request_uri;/*������url�ṹ*/
		char *body;/*��Ӧ��������*/
		char *status_code;/*�ַ�����ʽ״̬��*/
		int status_code_int;/*״̬��*/
		long body_length;/*�����峤��*/
		char *status_text;
		char *request_headers;/*����ͷ*/
		char *response_headers;/*��Ӧͷ*/
	}http_response;

	/**
	 * ����˵����
	 *   ����get����
	 * ������
	 *   url�������url��ַ
	 *   custom_header���Զ���ͷ��
	 *   paramName������Ĳ��������б�
	 *   paramValue������Ĳ���ֵ�б�
	 *   paramCount����������
	 * ����ֵ��
	 *   ������Ӧ�Ľṹ��ָ�룬ʹ�����֮����Ҫ����http_response_free�����ͷ�
	 */
	http_response* http_do_get(const char* url,const char* custom_headers,const char* paramName[],const char* paramValue[],int paramCount);

	/**
	 * ����˵����
	 *   ����post����
	 * ������
	 *   url�������url��ַ
	 *   custom_headers���Զ�������ͷ
	 *   post_data�������post�������ݣ����������ֻ����JSON��ʽ
	 * ����ֵ��
	 *   ������Ӧ�Ľṹ��ָ�룬ʹ�����֮����Ҫ����http_response_free�����ͷ�
	 */
	http_response* http_do_post(const char* url,const char* custom_headers,const char *post_data);


	/**
	 * ����˵����
	 *   �ͷ���Ӧ�ṹ���ڴ�
	 * ������
	 *   p_http_response����Ӧ�ṹָ��
	 */
	void http_response_free(http_response* p_http_response);

#ifdef __cplusplus
}
#endif

#endif