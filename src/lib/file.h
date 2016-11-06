/*
 * File:   file-array.h
 * Author: Yinka Ashon
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#ifndef FINSPECTOR_FILE_ARRAY_H
#define FINSPECTOR_FILE_ARRAY_H


/*
 * To ensure we enables "struct timespec" in time.h, we define
 * the followin
 */
#if __STDC_VERSION__ >= 199901L
#define _XOPEN_SOURCE 600
#else
#define _XOPEN_SOURCE 500
#endif /* __STDC_VERSION__ */
#include <time.h>
#include <stdint.h>
#include <sys/types.h>


#include "array.h"
#include "debug.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef enum {
    FI_FILE_TYPE_UNKNOWN,
    FI_FILE_TYPE_REGULAR,
    FI_FILE_TYPE_DIRECTORY,
    FI_FILE_TYPE_LINK,
    FI_FILE_TYPE_OTHER,
    FI_NUM_OF_FILE_TYPES
} FiFileType;

typedef struct FiFileInfo FiFileInfo_st;


#if (! defined(__timespec_defined))
    #define __timespec_defined 1
    // Following lines are copied from <time.h>
    # include <bits/types.h>	/* This defines __time_t for us.  */

    struct timespec {
        time_t      tv_sec;		/* Seconds.  */
        __int64_t   tv_nsec;	/* Nanoseconds.  */
    };
#endif

struct FiFileInfo {
    char               *filename;
    char               *file_path;
    char               *file_extension;
    off_t               size_byte;
    FiFileType          file_type;
    struct timespec     modified_at;
};

struct FiFileArray {
    struct FiArray   bank;
};

// File array
void fi_file_array_init(struct FiFileArray * array);
int  fi_file_array_add_file_info(struct FiFileArray *arr,
                                 struct FiFileInfo  *info);


#ifdef __cplusplus
}
#endif

#endif /* FINSPECTOR_FILE_ARRAY_H */

