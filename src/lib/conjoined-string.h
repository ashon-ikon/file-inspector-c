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

#ifndef FINSPECTOR_CONJOINED_STRING_H
#define FINSPECTOR_CONJOINED_STRING_H

#include "lib-common.h"

#include <stddef.h>

FI_BEGIN_DECLS

/* This bank holds all related strings separated by 
 * 'NUL' character
 */
struct FiHiStringBank {
	size_t		size;
	size_t		tip;
	unsigned char	wiped;
	char	       *strings;
};

/* This represent a fraction / bucket of string
 * within the bank
 */
struct FiHiString {
	size_t			offset;
	size_t			length;
	struct FiHiStringBank  *root;
};

#define FI_STR_BANK_AT(b, i)	((b)->strings + i)
#define FI_STR_BANK_SIZE(b)	((b)->size)
#define FI_STR_BANK_TIP(b)	((b)->tip)
#define FI_STR_BANK_IS_WIPED(b)	((b)->wiped == 1)

#define FI_STR_BANK(s)		((s)->root)
#define FI_STR_BANK_SIZE_STR(s)	FI_STR_BANK_SIZE(FI_STR_BANK((s)))
#define FI_STR_BANK_SIZE_TIP(s)	FI_STR_BANK_TIP(FI_STR_BANK((s)))
#define FI_STR_ADDR(s)		( \
		FI_STR_BANK_IS_WIPED(FI_STR_BANK((s))) ? \
		NULL : FI_STR_BANK_AT(FI_STR_BANK((s)), (s)->offset) )


struct FiHiStringBank *fi_conj_string_new();
void fi_conj_string_free(struct FiHiStringBank *bank);
struct FiHiString fi_conj_string_add(struct FiHiStringBank *b, const char *str);
void fi_conj_string_wipe_content(struct FiHiStringBank *b);
void fi_conj_string_wipe_content_quick(struct FiHiStringBank *b);

FI_END_DECLS

#endif /* FINSPECTOR_CONJOINED_STRING_H */

