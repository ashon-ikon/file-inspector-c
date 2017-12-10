/**
 * Author: Yinka Ashon
 * 
 * Handy module for printing error messages
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
 */

#include <stdlib.h>         // malloc
#include <stdio.h>
#include <stdarg.h>
#include <string.h>         // vargs

#include "debug.h"

#define FI_MSG_MAX          1024
#define FI_FN_MAX            128


/**
 * Handy method to print error messages
 * @param err
 * @param ...
 */
void _fi_log_message(FiDebugLevel type,
                    const char * fn, const int line, const char *file,
                    const char * err, ...)
{
    char  fname[FI_FN_MAX], msg[FI_MSG_MAX];

    short m = snprintf(fname, 128, "%s(%d) %s() ", file, line, fn);

    va_list ap;
    va_start(ap, err);
    vsnprintf(msg, FI_MSG_MAX - (m - 1), err, ap);
    va_end(ap);

    char t = ' ';
    switch(type) {

        case FI_DEBUG_LEVEL_ASSERT: t = 'A'; break;
        case FI_DEBUG_LEVEL_DEBUG:  t = 'D'; break;
        case FI_DEBUG_LEVEL_ERROR:  t = 'E'; break;
        case FI_DEBUG_LEVEL_INFO:   t = 'I'; break;
        case FI_DEBUG_LEVEL_WARN:   t = 'W'; break;
        case FI_DEBUG_LEVEL_VERB:   t = 'V'; break;
        default: break;
    }

    fprintf(stderr, "(%c%c) %s%s\n", t, t, fname, msg);
}
