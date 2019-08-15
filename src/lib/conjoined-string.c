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
#include "lib-common.h"

#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#include "conjoined-string.h"
#include "util-string.h"
#include "debug.h"

#define INITIAL_STRING_BUFFER_LENGTH    (1 << 8)
#define INITIAL_STRING_COUNT_SIZE       (1 << 3)

#define FI_D(p)                 (*(p))
#define FI_DD(p)               (**(p))

struct FiHiStringBank *fi_conj_string_new()
{
	struct FiHiStringBank *b = malloc(sizeof *b);

	if (!b)
		return NULL;

	*b->data = malloc(sizeof *b->data);
	*b->strs = malloc(sizeof *b->strs);

	b->size = 0;
	b->tip = 0;
	b->wiped = 1;
	b->strs_tip = 0;
	b->str_count = 0;

	return b;
}

void fi_conj_string_free(struct FiHiStringBank *bank)
{
	bank->size = 0;
	bank->tip = 0;
	bank->wiped = 1;
	bank->str_count = 0;
	bank->strs_tip = 0;
	fi_free(*bank->data);
	fi_free(bank->data);
	fi_free(*bank->strs);
	fi_free(bank->strs);
	fi_free(bank);
}

void fi_conj_string_zero_out_string(struct FiHiString *s)
{
	s->index = 0;
	s->mem_offset = 0;
	s->str_length = 0;
}

static int scale_string_size_up(struct FiHiStringBank *b, size_t ln)
{
	size_t str_size = sizeof FI_D(b->strs)[0];
	if (ln <= b->str_count) {
		fi_log_message_vf(FI_DEBUG_LEVEL_WARN,
			       "Invalid string bucket upsize requested. Current size %zu, requested size %zu",
			       b->str_count * str_size, ln * str_size);
		return FI_FUNC_FAIL;
	}
	size_t size =
	    fi_mem_best_size(MAX(b->str_count * 2, INITIAL_STRING_COUNT_SIZE),
			     b->strs_tip + ln);

	struct FiHiString *tmp = 
			realloc(FI_D(b->strs), (b->str_count + size) * str_size);
	
	if (!tmp) {
		fi_log_message_vf(FI_DEBUG_LEVEL_ERROR,
			       "Failed to upsize string memory area from %zu to %zu",
			       b->str_count * str_size, size * str_size);
		return FI_FUNC_FAIL;
	}

	FI_D(b->strs) = tmp;
	for (size_t i = b->str_count; i < (b->str_count + size); i++) {
		fi_conj_string_zero_out_string(&FI_D(b->strs)[i]);
		FI_D(b->strs)[i].root = b;	// Link back
	}
	b->str_count += size;

	return FI_FUNC_SUCCESS;
}

static int scale_string_size_down(struct FiHiStringBank *b, size_t ln)
{
	size_t str_size = sizeof FI_D(b->strs)[0];
	if (ln >= b->str_count) {
		fi_log_message_vf(FI_DEBUG_LEVEL_WARN,
			       "Invalid string bucket upsize requested. Current size %zu, requested size %zu",
			       b->str_count * str_size, ln * str_size);
		return FI_FUNC_FAIL;
	}
	size_t size = b->str_count / 2;
	size = size > ln ? size : fi_mem_best_size(MAX(ln, b->strs_tip), 32);

	struct FiHiString *tmp = realloc(FI_D(b->strs), size * str_size);
	if (!tmp) {
		fi_log_message_vf(FI_DEBUG_LEVEL_ERROR,
			       "Failed to downsize string memory area from %zu to %zu",
			       b->str_count * str_size, size * str_size);
		return FI_FUNC_FAIL;
	}
	FI_D(b->strs) = tmp;
	b->str_count += size;

	return FI_FUNC_SUCCESS;
}

static int scale_data_size_up(struct FiHiStringBank *b, size_t s)
{
	if (s + b->tip <= b->size) {
		fi_log_message_vf(FI_DEBUG_LEVEL_WARN,
			       "Invalid data upsize requested. Current size %zu, requested size %zu",
			       b->size, s);
		return FI_FUNC_FAIL;
	}

	size_t size =
	    fi_mem_best_size(MAX(b->size * 2, INITIAL_STRING_BUFFER_LENGTH),
			     b->tip + s);
	size_t unit_size = sizeof FI_D(b->data)[0];

	char *tmp = realloc(b->data, size * unit_size);
	if (!tmp) {
		fi_log_message_vf(FI_DEBUG_LEVEL_ERROR,
			       "Failed to upsize memory area from %zu to %zu",
			       b->size * unit_size, size * unit_size);
		return FI_FUNC_FAIL;
	}

	FI_D(b->data) = tmp;
	// Clear new memory area
	memset(FI_D(b->data) + b->size, 0, size - b->size);
	b->size = size;

	return FI_FUNC_SUCCESS;
}

static int scale_data_size_down(struct FiHiStringBank *b, size_t s)
{
	if (s >= b->size) {
		fi_log_message_vf(FI_DEBUG_LEVEL_WARN,
			       "Invalid data downsize requested. Current size %zu, requested size %zu",
			       b->size, s);
		return FI_FUNC_FAIL;
	}
	size_t size = b->size / 2;
	size_t struct_size = sizeof FI_D(b->data)[0];
	size = size > s ? size : fi_mem_best_size(s, 32);
	char *tmp = realloc(FI_D(b->data), size * struct_size);
	if (!tmp) {
		fi_log_message_vf(FI_DEBUG_LEVEL_ERROR,
			       "Failed to downsize memory area from %zu to %zu",
			       b->size * struct_size, size * struct_size);
		return FI_FUNC_FAIL;
	}
	FI_D(b->data) = tmp;
	b->size = size;

	return FI_FUNC_SUCCESS;
}

static int fi_conj_string_ensure_data_length(struct FiHiStringBank *b, size_t ln)
{
	size_t new_len = ln + 1;
	if (b->size > (b->tip + new_len)) {
		if (b->size > INITIAL_STRING_BUFFER_LENGTH
		    && b->size > (b->tip * 2)) {
			// We can shrink the size
			return scale_data_size_down(b, b->size / 2);
		}
		return FI_FUNC_SUCCESS;
	} else if (b->size == (b->tip + new_len)) {
		return FI_FUNC_SUCCESS;
	}

	return scale_data_size_up(b, new_len);
}

static int fi_conj_string_ensure_string_buckets(struct FiHiStringBank *b,
						size_t ln)
{
	if (b->str_count > (b->strs_tip + ln)) {
		if (b->str_count > INITIAL_STRING_COUNT_SIZE
		    && b->str_count > (b->strs_tip * 2)) {
			// We can shrink the size
			return scale_string_size_down(b, b->str_count / 2);
		}
		return FI_FUNC_SUCCESS;
	} else if (b->str_count == b->strs_tip + ln) {
		// Nothing required
		return FI_FUNC_SUCCESS;
	}

	return scale_string_size_up(b, b->strs_tip + ln);
}

static void string_add_common_treatment(struct FiHiStringBank *b,
					struct FiHiString *s, size_t len)
{
	if (FI_STR_BANK_IS_WIPED(b))
		b->wiped = 0;

	s->str_length = len;
	s->mem_offset = b->tip - len - 1;
	s->root = b;
}

/**
 * Inserts a new string into bank
 * @param b
 * @param s
 * @param str
 */
struct FiHiString *fi_conj_string_add(struct FiHiStringBank *b, const char *str)
{
	size_t len = fi_strlen(str);
	if (FI_FUNC_FAIL == fi_conj_string_ensure_data_length(b, len)
	    || FI_FUNC_FAIL == fi_conj_string_ensure_string_buckets(b, 1)) {
		return NULL;
	}
	strncpy(FI_STR_BANK_AT(b, b->tip), str, len);
	b->tip += len + 1;
	string_add_common_treatment(b, &FI_D(b->strs)[b->strs_tip], len);

	return &FI_D(b->strs)[b->strs_tip++];
}

struct FiHiString *fi_conj_string_add_concat(struct FiHiStringBank *b,
					     const unsigned char num, ...)
{
	char *words[num];
	size_t lengths[num], len = 0;
	va_list ap;
	va_start(ap, num);
	for (unsigned char i = 0; i < num; i++) {
		words[i] = va_arg(ap, char *);
		lengths[i] = fi_strlen(words[i]);
		len += lengths[i];
	}
	va_end(ap);

	if (len == 0
	    || FI_FUNC_FAIL == fi_conj_string_ensure_data_length(b, len)
	    || FI_FUNC_FAIL == fi_conj_string_ensure_string_buckets(b, 1)) {
		return NULL;
	}
//printf("R: %p, d %p ", b, b->data);
	for (unsigned char i = 0; i < num; i++) {
//printf(" st %p <%lX> ", b->data + b->tip, b->tip);
		strncpy(FI_STR_BANK_AT(b, b->tip), words[i], lengths[i]);
		b->tip += lengths[i];
	}
//printf("\n");
	*FI_STR_BANK_AT(b, b->tip++) = '\0';
	string_add_common_treatment(b, &FI_D(b->strs)[b->strs_tip], len);

	return &FI_D(b->strs)[b->strs_tip++];
}

void fi_conj_string_remove_last(struct FiHiStringBank *b)
{
	if (!b)
		return;

	struct FiHiString *last = &FI_D(b->strs)[b->strs_tip - 1];
	*FI_STR_ADDR(last) = '\0';

	b->tip = last->mem_offset;
	fi_conj_string_zero_out_string(last);
	b->strs_tip = --b->strs_tip < 0 ? 0 : b->strs_tip;
//      fi_conj_string_ensure_data_length(b, b->tip);
//      fi_conj_string_ensure_string_buckets(b, 0);

	return;
}

/**
 * This wipes the data content and resets tip
 * @param b
 */
void fi_conj_string_wipe_content(struct FiHiStringBank *b)
{
	if (!b)
		return;

	fi_conj_string_wipe_content_quick(b);

	memset(FI_D(b->data), 0, sizeof(FI_D(b->data)[0]) * b->size);
}

void fi_conj_string_wipe_content_quick(struct FiHiStringBank *b)
{
	if (!b)
		return;

	for (size_t i = 0; i < b->str_count; i++) {
		fi_conj_string_zero_out_string(&FI_D(b->strs)[i]);
	}
	b->strs_tip = 0;
	for (size_t i = 0; (i < b->size || i < 4); i++) {
		// Just null off first 4 chars
		*((char *)FI_STR_BANK_AT(b, i)) = '\0';
	}
	b->tip = 0;
	b->wiped = 1;
}
