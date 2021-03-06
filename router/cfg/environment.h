
/**************************************
 * This file is a configuration file.
 * coding by: haoran dai
 * time:2018-4-29 20:53
 **************************************/
#ifndef _ENVIRONMENT_H
#define _ENVIRONMENT_H

#ifdef _MSC_VER/* only support win32 and greater. */
#define MS_WINDOWS
#endif

#ifdef __linux /**only suport linux platform*/
#define LINUX
#endif

/*define NULL */
#ifndef NULL
#define NULL 0
#endif

/*define bool*/
#ifndef bool
#define bool unsigned int
#define true 1
#define false 0
#endif

#ifdef MS_WINDOWS
/*define windows platform configuration file path*/
#define MOON_CONF_PATH ".\\config" /*define moon configuration dir*/
#define MOON_SERVER_CONF_FILE ".\\config\\router.cfg" /* server configuration file path*/
#define MOON_CONF_FILE_SIZE 1024*1024 /*define config file size*/
#define MOON_LOG_FILE_NAME "router.log" /*server log path*/
#endif

#ifdef LINUX
/*define linux platform configuration file path*/
#define MOON_CONF_PATH "config" /*define moon configuration dir*/
#define MOON_SERVER_CONF_FILE "config/router.cfg" /* server configuration file path*/
#define MOON_CONF_FILE_SIZE 10240 /*define config file size*/
#define MOON_LOG_FILE_NAME "log/router.log" /*server log path*/
#endif

/*define the param characteristic*/
#define _in_    //Input parameter
#define _out_   //output paramter

#define _global_ //定义全局变量的时候使用



/**
 * 定义配置结构体
 */
typedef struct _router_server_config{
	char register_addr[512];//注册中心地址
	char server_ip[30];//服务启动ip
	int server_port;//服务端口
	int http_port;//http服务的端口
	char router_node_name[60];//节点名称
	int moon_node_max_count;//管理的通信服务节点最大数量
	char log_level_debug;//是否开启debug日志
	char log_level_info;//是否开启info日志
	char log_level_warnning;//是否开启警告
	char log_level_error;//是否开启error日志
}router_server_config;


#endif
