/*
 * File:   detector.h
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
 * Created on 27 September 2016, 3:47 PM
 */


#ifndef FINSPECTOR_FILE_DETECTOR_H
#define FINSPECTOR_FILE_DETECTOR_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 -----------------------------------
 File Info
 */


typedef enum {
    FI_FILE_TYPE_UNKNOWN,
    FI_FILE_TYPE_REGULAR,
    FI_FILE_TYPE_DIRECTORY,
    FI_FILE_TYPE_LINK,
    FI_FILE_TYPE_OTHER,
    FI_NUM_OF_FILE_TYPES
} FiFileType;


typedef struct _FiFileInfo FiFileInfo;
typedef struct _FiFileList FiFileList;

struct _FiFileInfo {
    char              * filename;
    char              * file_path;
    char              * file_extension;
    off_t               size_byte;
    FiFileType          file_type;
    struct timespec     modified_at;
};

// File List structure
// This holds the individual file information
struct _FiFileList {
    uint64_t length;
    uint64_t capacity;
    FiFileInfo ** pfile_info_list;
};

/**
 * Types of Duplicates to detect
 */
#define FI_DUPLICATE_FILENAME               1 << 0;
#define FI_DUPLICATE_FILE_SIZE              1 << 1;
#define FI_DUPLICATE_MODIFICATION_TIME      1 << 2;
#define FI_DUPLICATE_ALL                    0x0F;


// ---------------------------------------
// Helper methods
/**
 * Returns a pre-populated FileList structure
 * @param src
 * @param recursive
 * @return 
 */
FiFileList *
fi_file_list_get_list_from_source_m(const char * src, bool recursive);

#ifdef __cplusplus
}
#endif

#endif /* FINSPECTOR_FILE_DETECTOR_H */

