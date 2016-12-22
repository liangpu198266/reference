/*
 * Copyright (C) sunny liang
 * Copyright (C) mini net cmd
 */

#ifndef __LOGPRINT_H__
#define __LOGPRINT_H__

#include "common.h"

/********print debug**********/

#if defined DEBUG_TO_SYSLOG

#define NETCMD_ASSERT(exp)                  do{ assert(exp); } while(0)
#define NETCMD_DBG(args...)                 syslog(LOG_INFO, args)
#define NETCMD_WARN(args...)                syslog(LOG_WARNING, args)
#define NETCMD_ERROR(args...)               syslog(LOG_ERR, args)

#elif defined DEBUG_TO_SCREEN 

#define NETCMD_ASSERT(exp)                  do{ assert(exp); } while(0)
#define NETCMD_DBG(format, arg...)          do{ fprintf(stderr, "[INFO] %s@Line%d : " format "\n", __FUNCTION__, __LINE__,  ## arg); fflush(stderr); } while(0)
#define NETCMD_WARN(format, arg...)         do{ fprintf(stderr, "[WARN] %s@Line%d : " format "\n", __FUNCTION__, __LINE__,  ## arg); fflush(stderr); } while(0)
#define NETCMD_ERROR(format, arg...)        do{ fprintf(stderr, "[ERROR] %s@Line%d : " format "\n", __FUNCTION__, __LINE__,  ## arg); fflush(stderr); } while(0)

#elif defined DEBUG_TO_FILE 

#define DEBUG_ERROR   1
#define DEBUG_WARNING 2
#define DEBUG_INFO    3

#define NETCMD_ASSERT(exp)                  do{ assert(exp); } while(0)
#define NETCMD_DBG(fmt...)                  netcmdPrintf(DEBUG_INFO, __func__, fmt) 
#define NETCMD_WARN(fmt...)                 netcmdPrintf(DEBUG_WARNING, __func__, fmt) 
#define NETCMD_ERROR(fmt...)                netcmdPrintf(DEBUG_ERROR, __func__, fmt) 

#else

#define NETCMD_ASSERT(exp)                  do{ (void) 0; } while(0)
#define NETCMD_DBG(format, arg...)          do{ (void) 0; } while(0)
#define NETCMD_WARN(format, arg...)         do{ (void) 0; } while(0)
#define NETCMD_ERROR(format, arg...)        do{ fprintf(stderr, "[ERROR]: " format "\n", ## arg); fflush(stderr); } while(0)

#endif

extern int8 initFileLogSystem(void);
extern void finiFileLogSystem(void);

#endif

