/**********************************************************************************
文 件 名:LWZSocket.h
描    述:公共头文件
作    者:卢磊
时    间:2017/4/14
修    改:
**********************************************************************************/

/*********************************************************************************
#ifndef __LWZSOCKET_H__
#define __LWZSOCKET_H__

#endif
*********************************************************************************/

#ifndef __COMMON_H__
#define __COMMON_H__

//类型定义
typedef signed char s8;         /* 有符号8位整型 */
typedef unsigned char u8;       /* 无符号8位整型 */

typedef signed short s16;       /* 有符号16位整型 */
typedef unsigned short u16;     /* 无符号16位整型 */

typedef signed int s32;         /* 有符号32位整型 */
typedef unsigned int u32;       /* 无符号32位整型 */

typedef signed long long s64;   /* 有符号64位整型 */
typedef unsigned long long u64; /* 无符号64位整型 */

//DEBUG级别系统日志
#define dbg(fmt, arg...) \
    do { \
        if (DEBUG_ON == g_debug_switch) { \
            syslog(LOG_DEBUG, "[RK] %s(%d) " fmt, __func__, __LINE__, ##arg);\
        }\
    } while (0)

/* INFO级别系统日志，无串口输出 */
#define msg(fmt, arg...) \
    do { \
        syslog(LOG_INFO, "[RK] %s(%d) " fmt, __func__, __LINE__, ##arg);\
    } while (0)

/* 正常信息打印，产品正式运行时记录INFO级别系统日志，同时在串口输出 */
#define prt(fmt, arg...) \
	do { \
        printf("[RK] %s(%d) " fmt, __func__, __LINE__, ##arg);\
	}while(0)

/* 错误信息打印，任何时候都记录ERROR级别系统日志，同时在串口输出 */
#define err(fmt, arg...) \
	do { \
        printf("[err] %s(%d) Error, " fmt, __func__, __LINE__, ##arg);\
	}while(0)


#endif