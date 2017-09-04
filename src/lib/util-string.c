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
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "util-string.h"

static bool found_char_within(const char *c, const char *impurities)
{
    while (*impurities != '\0') {
        if (*c == *impurities) {
            return true;
        }
        impurities++;
    }

    return false;
}

/**
 *  Trims string str removing any occurrence of any of the impurities chars
 *  from the rightmost parts of str
 */
char * fi_rtrim(char * str, const char * impurities)
{
    if (str == NULL || impurities == NULL)
        return NULL;

    for (size_t i = strlen(str) - 1; i >= 0; i--) {
        if (found_char_within(&str[i], impurities)) {
            str[i] = '\0';
        } else {
            // No need to keep checking
            break;
        }
    }

    return str;
}

/**
 *  Trims string str removing any occurrence of any of the impurities chars
 *  from the leftmost parts of str.
 *  Note, this also tries to move the chars to the left for sanity sake
 */
char * fi_ltrim(char * str, const char * impurities)
{
        if (str == NULL || impurities == NULL)
            return NULL;
        int last_pos = -1;
        for (size_t i = 0; i <= strlen(str); i++) {
            if (found_char_within(&str[i], impurities)) {
                last_pos = (int)i;
            } else {
                // No need to keep checking
                break;
            }
        }

        if (last_pos == -1) {
                return str;
        }
        // Clean up for any potential leading null strings
        char *x = str;
        
        last_pos++;
        size_t len_x = fi_strlen(&x[last_pos]);
        char *temp = fi_strndup(&x[last_pos], len_x);
        strncpy(str, temp, len_x + 1); // Copy over source memory
        str[len_x] = '\0';
        free(temp);

        return str;
}

char * fi_trim(char * str, const char * impurities)
{
    str = fi_rtrim(str, impurities);
    str = fi_ltrim(str, impurities);

    return str;
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
    if (! src) return NULL;

    size_t n = 0;
    const char *dup = src;
    while(*dup++ != '\0') n++;

    return _fi_strndup(src, n);
}

char *_fi_strndup(const char *src, size_t n)
{
    char *dup = NULL;
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

int fi_strcmp0(const char const *s1, const char const *s2)
{
    return strcmp(s1, s2) == 0;
}

/**
 * 
 * @param i
 * @param str
 * @param base
 * Only bases 2 to 16 are supported
 * @see Inspired by http://stackoverflow.com/a/9660930
 */
char *itoa(const int i, char *str, unsigned base)
{
    char const digit[] = "0123456789ABCDEF";
    char* p = str;
    int n = i;

    if (base < 2 || base > 16){
        *p = '\0';
        return str;
    }

    if (n < 0) {
        *p++ = '-';
        n *= -1;
    }
    
    // Shift char pointer to the least 10's
    int shifter = n;
    do { 
        ++p;
        shifter = shifter / base;
    } while (shifter);

    *p = '\0'; // Terminate the string
    do { 
        //Move back, inserting digits as u go
        *--p = digit[n % base];
        n = n / base;
    } while (n);

    return str;
}