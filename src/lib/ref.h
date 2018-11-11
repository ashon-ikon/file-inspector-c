/* 
 * File:   ref.h
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
 * Created on 4 November 2016, 5:03 PM
 */

#ifndef REF_H
#define REF_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Greatly inspired by Chris Wellon's demonstration of the same
 * http://nullprogram.com/blog/2015/02/17/
 */
#ifndef container_of
#define container_of(ptr, type, member) ((type *) \
    ((unsigned long *)(1 ? (ptr) : &((type *)0)->member) - offsetof(type, member)))
#endif
    
#define fi_free_ref_object(p_object)        \
    do {                                    \
        fi_ref_dec(&((p_object)->ref));     \
    } while(0)

// ------------------------
// Reference counter struct
struct FiRef {
    int  count;
    void (*free)(const struct FiRef *ref);
};


// Inline methods
static inline int fi_ref_inc(const struct FiRef *ref)
{
    int t = ((struct FiRef *)ref)->count++;

    return t >= 0 ? 0 : -1;
}

static inline int fi_ref_dec(const struct FiRef *ref)
{
    int t = --((struct FiRef *)ref)->count;

    if (t == 0 && ((struct FiRef *)ref)->free)
        ((struct FiRef *)ref)->free(ref);
    
    return t >= 0 ? 0 : -1;
}

#ifdef __cplusplus
}
#endif

#endif /* REF_H */

