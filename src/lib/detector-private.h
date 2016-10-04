/** 
 * File:   detector-private.h
 * 
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

 *
 * Created on 27 September 2016, 7:48 PM
 */

#ifndef FINSPECTOR_FILE_DETECTOR_PRIVATE_H
#define FINSPECTOR_FILE_DETECTOR_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "detector.h"

    
/**
 * Returns an empty
 * @return FiFileList
 */
static FiFileList *
fi_file_list_new ();

static FiFileList *
fi_file_list_add (FiFileList * self, FiFileInfo * file_info);

static FiReturnResponse
resize_list_if_required(FiFileList * list, size_t size);

static bool
fi_file_list_free (FiFileList * self);

static void
fi_print_error(const char * err, ...);

#ifdef __cplusplus
}
#endif

#endif /* FINSPECTOR_FILE_DETECTOR_PRIVATE_H */

