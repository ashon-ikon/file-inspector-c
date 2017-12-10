/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   lib-common.h
 * Author: yasonibare
 *
 * Created on 5 October 2016, 11:44 AM
 */

#ifndef LIB_COMMON_H
#define LIB_COMMON_H

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdlib.h>

#ifndef __BEGIN_DECLS
    #ifdef __cplusplus
        #define __BEGIN_DECLS extern "C" {
        #define __END_DECLS }
    #else
        #define __BEGIN_DECLS
        #define __END_DECLS
    #endif
#endif

#define FI_BEGIN_DECLS  __BEGIN_DECLS
#define FI_END_DECLS    __END_DECLS


FI_BEGIN_DECLS

typedef enum {
    FI_SUCCESS          = 0,
    FI_ERROR_OUT_OF_MEM = 1 << 1,
    FI_ERROR_NULL_VALUE = 1 << 2
} FiReturnResponse;

#ifndef FI_FUNC_RESPONSES
#define FI_FUNC_FAIL            -1
#define FI_FUNC_SUCCESS          0
#define FI_FUNC_RESPONSES       0x1200
#endif

#ifdef __GNUC__
#define fi_checkprintf  __attribute__ (( format(printf, 1, 2) ))
#else
#define fi_checkprintf
#endif

#ifndef MAX
    #define MAX(a, b)       ((a) > (b) ? (a) : (b))
#endif

#ifndef MIN
    #define MIN(a, b)       ((a) < (b) ? (a) : (b))
#endif

inline void fi_free(const void *p)
{
    if (p) free(p);
}

FI_END_DECLS

#endif /* LIB_COMMON_H */

