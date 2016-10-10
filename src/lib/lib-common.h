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

#ifdef __cplusplus
extern "C" {
#endif


typedef enum {
    FI_SUCCESS          = 0,
    FI_ERROR_OUT_OF_MEM = 1 << 1,
    FI_ERROR_NULL_VALUE = 1 << 2
} FiReturnResponse;


#ifdef __cplusplus
}
#endif

#endif /* LIB_COMMON_H */

