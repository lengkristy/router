/************************************************************************
 * this file used to parse system configuration file 
 * coding by: haoran dai
 * time:2018-5-1 21:56                               
 ***********************************************************************/
#pragma once
#ifndef _MODULE_LOG_H
#define _MODULE_LOG_H
#include "../cfg/environment.h"

#ifdef __cplusplus
extern "C" {
#endif

bool load_config(router_server_config* pConf);//load configuration file

#ifdef __cplusplus
}
#endif

#endif