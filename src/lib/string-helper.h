/* 
 * File:   string-helper.h
 * Author: yasonibare
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
 * Created on 30 September 2016, 5:32 PM
 */

#ifndef FINSPECTOR_STRING_HELPER_H
#define FINSPECTOR_STRING_HELPER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>

/**
 * Duplicates given string.
 * 
 * result must be freed when done!
 * 
 * @param src
 * @return char*
 */
char *
fi_strdup(const char * src);

char *
fi_strndup(const char * src, const size_t len);

char *
fi_sstrdup(const char * frm, ...);

char *
fi_vsstrdup(const char * frm, va_list ap);


#ifdef __cplusplus
}
#endif

#endif /* FINSPECTOR_STRING_HELPER_H */

