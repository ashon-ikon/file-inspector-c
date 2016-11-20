/* 
 * File:   util-string.h
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

#ifndef FINSPECTOR_UTIL_STRING_H
#define FINSPECTOR_UTIL_STRING_H

#include <string.h>

#include "lib-common.h"

FI_BEGIN_DECLS


// #if defined (_XOPEN_SOURCE) \ -
//    || /* Since glibc 2.12: */ defined _POSIX_C_SOURCE \ -
//    || /* Glibc versions <= 2.19: */ defined _BSD_SOURCE \ -
//    || defined _SVID_SOURCE
//
//    #define fi_strdup(s)   strdup( (s) )
//    #define fi_strndup(s, n)  strndup( (s), (n) )
// #else
    // Probably windows or some sort
    #define FI_NO_STRDUP_FOUND
    #define fi_strdup(s)      _fi_strdup( (s) )
    #define fi_strndup(s, n)  _fi_strndup( (s), (n) )
// #endif

char *fi_rtrim(char * str, const char * impurities);
char *fi_ltrim(char * str, const char * impurities);
char *fi_trim(char * str, const char * impurities);

#ifdef FI_NO_STRDUP_FOUND
/* Platform appears not to have support for strdup and strndup
 */
char *_fi_strdup (const char *src);
char *_fi_strndup(const char *src, size_t n);
#endif

FI_END_DECLS

#endif /* FINSPECTOR_UTIL_STRING_H */

