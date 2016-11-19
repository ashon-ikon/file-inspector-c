/*
 * File:   debug.h
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
 * Created on 5 October 2016, 11:28 AM
 */

#ifndef FINSPECTOR_DEBUG_H
#define FINSPECTOR_DEBUG_H

#include <stdarg.h>
#include <string.h>

#include "lib-common.h"

FI_BEGIN_DECLS

#if __STDC_VERSION__ >= 199901L
    #ifndef __FUNC__
    #define __FUNC__ __func__
    #endif
#else
    #define __FUNC__    ""
#endif
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define fmt_printf __attribute__((format(printf, 5, 6)))
    
typedef enum {
    FI_DEBUG_LEVEL_CRITICAL,
    FI_DEBUG_LEVEL_ERROR,
    FI_DEBUG_LEVEL_FATAL,
    FI_DEBUG_LEVEL_INFO,
    FI_DEBUG_LEVEL_WARN,

} FiMessageType;

void _fi_log_message(FiMessageType level,
                    const char * fn, const int line, const char *file,
                    const char * err, ...) fmt_printf;

#define fi_log_message(lv, fmt, ...) do {                   \
                _fi_log_message((lv),                       \
                __FUNC__, __LINE__, __FILENAME__, (fmt) , ##__VA_ARGS__); \
            } while(0)

FI_END_DECLS

#endif /* FINSPECTOR_DEBUG_H */

