/* 
 * File:   conjoined-string.h
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

#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#include "conjoined-string.h"
#include "util-string.h"

#define INITIAL_STRING_BUFFER_LENGTH    (1 << 8)

struct FiHiStringBank *fi_conj_string_new()
{
        struct FiHiStringBank *b = malloc(sizeof(*b));
        
        if (!b) return NULL;
        
        b->size = 0;
        b->tip = 0;
        b->wiped = 1;
        b->strings = NULL;
        b->last_string = NULL;
        
        return b;
}

void fi_conj_string_free(struct FiHiStringBank *bank)
{
        bank->size = 0;
        bank->tip = 0;
        bank->wiped = 1;
        fi_free(bank->strings);
        fi_free(bank);
}

static int fi_conj_string_ensure_length(struct FiHiStringBank *b, size_t l)
{
        size_t new_len = l + 1;
        if (b->size > (b->tip + new_len)) return FI_FUNC_SUCCESS;
        
        size_t size = fi_mem_best_size(
                                MAX(b->size * 2, INITIAL_STRING_BUFFER_LENGTH),
                                new_len);
        char *tmp = realloc(b->strings, size * sizeof b->strings[0]);
        if (!tmp) return FI_FUNC_FAIL;

        b->strings = tmp;
        memset(b->strings + b->size, 0, size); // Clear new memory area
        b->size = size;
        
        return FI_FUNC_SUCCESS;
}

/**
 * Inserts a new string into bank
 * @param b
 * @param s
 * @return
 */
void fi_conj_string_add(struct FiHiStringBank *b,
                       const char *str,
                       struct FiHiString *s)
{
        size_t len = fi_strlen(str);
        fi_conj_string_ensure_length(b, len);
        
        memcpy(FI_STR_BANK_AT(b, b->tip), str, len);
        
        if (FI_STR_BANK_IS_WIPED(b)) b->wiped = 0;
        
        s->length = len;
        s->offset = b->tip;
        s->root = b;
        if (b->last_string) {
                s->prev = b->last_string;
                b->last_string->next = s;
        } else {
                s->prev = NULL;
        }
        s->next = NULL;
        b->tip += len + 1;
        b->last_string = s;

        return;
}

static void fi_conj_string_unlink(struct FiHiString *s)
{
       if (s->next) s->next->prev = s->prev;
       if (s->prev) s->prev->next = s->next;
       s->length = 0;
       s->offset = 0;
       *FI_STR_ADDR(s) = '\0';
       s->next = NULL;
       s->prev = NULL;
}

void fi_conj_string_remove_last(struct FiHiStringBank *b)
{
        if (!b)
                return;
        if (!b->last_string)
                return;
        
        struct FiHiString *s = b->last_string;

        b->tip -= s->length;
        b->last_string = s->prev ? s->prev: NULL;
        b->last_string->next = NULL;
        s->length = 0;
        s->offset= 0;
        *FI_STR_ADDR(s) = '\0';

        return;
}

/**
 * This wipes the data content and resets tip
 * @param b
 */
void fi_conj_string_wipe_content(struct FiHiStringBank *b)
{
        if (!b) return;
        
        fi_conj_string_wipe_content_quick(b);
        
        memset(b->strings, 0, sizeof(b->strings[0]) * b->size);
}

void fi_conj_string_wipe_content_quick(struct FiHiStringBank *b)
{
        if (!b) return;
        
        struct FiHiString *tail = b->last_string, *p;

        while (tail) {
                p = tail->prev;
                fi_conj_string_unlink(tail);
                tail = p;
        }
        
        b->wiped = 1;
}