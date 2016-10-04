/*
 * File:   string-helper.c
 * Author: Yinka Ashon
 * 
 * Common string manipulation methods
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

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "string-helper.h"

/**
 * Duplicates the given string
 * 
 * @param src
 * @return 
 */
char *
fi_strdup(const char * src)
{
    // Ensure src is valid
    size_t len = strlen(src) + 1;
    // Attempt to create a new memory space
    char * tmp = malloc(len);
    
    return tmp ? memcpy(tmp, src, len) : NULL;
}

/**
 * Duplicates the given string
 * 
 * @param src
 * @return 
 */
char *
fi_strndup(const char * src, const size_t len)
{
    // Attempt to create a new memory space
    char * tmp = malloc(len + 1); // Add one for terminator

    if (tmp != NULL) {
        tmp[len] = '\0';
        tmp = memcpy(tmp, src, len);
    }
    
    return tmp;
}

/**
 * Attempts to clone formated list with ...
 * @param frm
 * @param ...
 * @return 
 */
char *
fi_sstrdup(const char * frm, ...)
{
    char c[1] /* dummy string */, *p_string;
    
    va_list a_list;
    
    // --------------------
    // Unpack the string
    // This is just to get the potential size of the final string
    va_start(a_list, frm);
    size_t len = vsnprintf(c, 1, frm, a_list) + 1; // Bad hack
    va_end(a_list);
    
    // Create new string based on new length
    p_string = malloc(len);
    
    if (p_string) {
        va_start(a_list, frm);
        vsnprintf(p_string, len, frm, a_list);
        va_end(a_list);
    }
    
    return p_string;
}

/**
 * Attempts to clone formated string with va_list
 * @param frm
 * @param ap
 * @return 
 */
char *
fi_vsstrdup(const char * frm, va_list ap)
{
    char c /* dummy string */, *p_string;
    va_list c_ap;
    va_copy(c_ap, ap); // Copy it before first usage
    size_t len = vsnprintf(&c, 1, frm, ap) + 1; // Hack, to get length
    // Create new string based on new length
    p_string = malloc(len); 
    if (p_string) {
        vsnprintf(p_string, len, frm, c_ap);
    }

    return p_string;
}