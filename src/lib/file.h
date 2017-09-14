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

#include <time.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>

#include "lib-common.h"

#include "array.h"
#include "debug.h"
#include "ref.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef PATH_MAX
#ifdef _POSIX_VERSION
#define PATH_MAX _POSIX_PATH_MAX
#else
#ifdef MAXPATHLEN
#define PATH_MAX MAXPATHLEN
#else
#define PATH_MAX 1024
#endif
#endif
#endif
    
#ifndef FI_FUNC_RESPONSES
#define FI_FUNC_FAIL            -1
#define FI_FUNC_SUCCEED          0
#define FI_FUNC_RESPONSES       0x1200
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
    # include <bits/types.h>	/* This defines time_t for us.  */

    struct timespec {
        time_t      tv_sec;	/* Seconds.  */
        int64_t     tv_nsec;	/* Nanoseconds.  */
    };
#endif

struct FiFileInfo {
    char               *filename;
    char               *path;
    char               *extension;
    off_t               size_byte;
    bool                free_container;
    FiFileType          type;
    struct timespec     modified_at;
    struct FiRef        ref;
};

#define FI_FILE_INIT(f) struct FiFileInfo (f); fi_file_init(&(f))
#define FI_FILE_FREE(f) (f); fi_file_destroy(&(f))

void fi_file_init(struct FiFileInfo *file);
void fi_file_destroy(struct FiFileInfo *file);
bool fi_file_copy(const FiFileInfo_st *src, FiFileInfo_st *dest);
void fi_file_set_props(struct FiFileInfo *file,
                       const char *filename,
                       const char *path,
                       const char *extension,
                       off_t size,
                       struct timespec modified_at,
                       void (*free)(const struct FiRef *ref));

bool fi_file_copy_proxy(void const *src, void *dst, unsigned n); // Copy method

#ifdef __cplusplus
}
#endif

#endif /* FINSPECTOR_FILE_ARRAY_H */

