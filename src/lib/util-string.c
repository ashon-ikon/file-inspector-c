/*
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
#include <stddef.h>
#include <stdlib.h>

#include "util-string.h"

char * fi_rtrim(char * str, const char * impurities)
{
    char * x = NULL;
    return x;
}

char * fi_ltrim(char * str, const char * impurities)
{
    char * x = NULL;
    return x;
}

char * fi_trim(char * str, const char * impurities)
{
    char * x = NULL;
    return x;
}

size_t fi_strlen(const char const* s)
{
    return (! s) ? 0 : strlen(s);
    
}

#if defined FI_NO_STRDUP_FOUND
/* Platform appears not to have support for strdup and strndup
 */
char *_fi_strdup (const char *src)
{
    size_t n = 0;
    const char *dup = src;
    while(*dup++ != '\0') n++;

    return _fi_strndup(src, n);
}

char *_fi_strndup(const char *src, size_t n)
{
    char *dup = NULL;
    const char *tmp;
       
    tmp = src;
    if (! src)
        return NULL;
    
    if (n <= 0)
        return NULL;
    
    dup = malloc(n + 1);
    memcpy(dup, src, n);
    dup[n] = '\0';
    
    return dup;
}
#endif

char * fi_strconcat(const unsigned char num, ...)
{
    if (num < 1)
        return NULL;

    unsigned int  len = 0;
    unsigned char i = 0;
    char          *words[num];

    va_list ap;
    va_start(ap, num);
    for (i = 0; i < num; i++) {
        words[i] = va_arg(ap, char*);
        len += strlen(words[i]);
    }
    va_end(ap);
    
    // Let's create the final string
    char *str = malloc(len + 1);
    if (! str)
        return NULL;
    str[0] = '\0';

    for (i = 0; i < num; i++)
        strncat(str, words[i], strlen(words[i]));

    return str;
}