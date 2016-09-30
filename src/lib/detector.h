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

#include <stdint.h>

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
} FiFileType;

typedef struct _FiFileInfo FiFileInfo;
typedef struct _FiFileList FiFileList;

struct _FiFileInfo {
    char * filename;
    char * file_path;
    FiFileType file_type;
    char * file_extension;
};

// File List structure
// This holds the individual file information
struct _FiFileList {
    FiFileInfo ** pfile_info_list;
    uint64_t length;
    uint64_t capacity;
};


// Helper methods



#ifdef __cplusplus
}
#endif

#endif /* FINSPECTOR_FILE_DETECTOR_H */

