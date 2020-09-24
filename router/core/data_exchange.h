/***************************************************************************
 * 文件说明：
 *       该模块主要是与注册中心进行数据交换，通过http的方式获取数据以及提交数据
 *
 ***************************************************************************/

#ifndef _DATA_EXCHANGE_H
#define _DATA_EXCHANGE_H

#include "../cfg/environment.h"

#ifdef __cplusplus
extern "C" {
#endif

	/**
	 * 函数说明：
	 *    启动数据交换服务
	 * 参数说明：
	 *    p_router_server_config：服务配置
	 */
	void start_data_exchange_service( router_server_config *p_router_server_config );

	/**
	 * 函数说明：
	 *    停止数据交换服务
	 */
	void stop_data_exchange_service();

#ifdef __cplusplus
extern "C" {
#endif

#endif