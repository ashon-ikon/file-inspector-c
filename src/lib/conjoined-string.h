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
#include <stdarg.h>

FI_BEGIN_DECLS

struct FiHiString;

/* This bank holds all related strings separated by 
 * 'NUL' character
 */
struct FiHiStringBank {
	/*
	 * total number of bytes occupied by the bank */
	size_t size;
	/*
	 * The tip of the data */
	size_t tip;
	/*
	 * index to tip of strings */
	size_t strs_tip;
	/*
	 * no. of string available */
	size_t str_count;
	/*
	 * Pointer to the pointer of the data segment holding the actual data.
	 * 
	 * Since the actual data segment needs to be relocated from time to
	 * time, we can only ever seek to hold a pointer to the location of the 
	 * pointer of the data */
	struct FiHiString **strs;
	/*
	 * Pointer to the pointer of the actual string data
	 * 
	 * Same as above, this data segment may need to be moved around as
	 * per the needs of the application, so we store only the reference 
	 * pointer to the pointer */
	char **data;

	/*
	 * This is a handy flag to keep track the freshness of our bank.
	 * 
	 * It will be 1 when something of value is written into the bank */
	unsigned char wiped;
};

/* This represent a fraction / bucket of string
 * within the bank
 */
struct FiHiString {
	/*
	 * This represent the index of this string in the bank */
	size_t index;
	/*
	 * this is the offset in the physical memory location */
	size_t mem_offset;
	/*
	 * This is the logical length the string occupies */
	size_t str_length;
	/*
	 * Points to the bank it is associated with */
	struct FiHiStringBank *root;
};

#define FI_STR_BANK_DATA_P(b)	(*((b)->data))
#define FI_STR_BANK_AT(b, i)    ((char*)FI_STR_BANK_DATA_P(b) + (i))
#define FI_STR_BANK_SIZE(b)     ((b)->size)
#define FI_STR_BANK_TIP(b)      ((b)->tip)
#define FI_STR_BANK_IS_WIPED(b) ((b)->wiped == 1)

#define FI_STR_BANK(s)             ((s)->root)
#define FI_STR_BANK_SIZE_STR(s)    FI_STR_BANK_SIZE(FI_STR_BANK((s)))
#define FI_STR_BANK_SIZE_TIP(s)    FI_STR_BANK_TIP(FI_STR_BANK((s)))
#define FI_STR_ADDR(s)             ( \
                FI_STR_BANK_IS_WIPED(FI_STR_BANK((s))) ? \
                NULL : FI_STR_BANK_AT(FI_STR_BANK((s)), (s)->mem_offset) )
#define FI_STR_BANK_LAST_STRING(b)  ( \
             b->strs_tip == 0 ? NULL : \
                ( \
                        FI_STR_ADDR(&((b)->strs[(b)->strs_tip - 1])) \
                ) )

struct FiHiStringBank *fi_conj_string_new();
void fi_conj_string_free(struct FiHiStringBank *bank);
struct FiHiString *fi_conj_string_add(struct FiHiStringBank *b,
				      const char *str);
struct FiHiString *fi_conj_string_add_concat(struct FiHiStringBank *b,
					     const unsigned char num, ...);
void fi_conj_string_remove_last(struct FiHiStringBank *b);
void fi_conj_string_wipe_content(struct FiHiStringBank *b);
void fi_conj_string_wipe_content_quick(struct FiHiStringBank *b);

FI_END_DECLS

#endif				/* FINSPECTOR_CONJOINED_STRING_H */
