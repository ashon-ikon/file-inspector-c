/* 
 * File:   algo.c
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

#include "algo-core.h"

//static bool fi_algo_copy_proxy(void const *src, void *dst, unsigned n);
//static bool fi_algo_copy(const struct FiAlgo const *src, struct FiAlgo *dst);
//static char fi_algo_collection_add(struct FiAlgoCollection *self,
//                                   struct FiAlgo *algo);

void fi_algo_collection_init(struct FiAlgoCollection *coll)
{
    if (! coll)
        return;
    
//    coll->add       = fi_algo_collection_add;
//    coll->algos     = fi_array_new(sizeof (struct FiAlgo), fi_algo_copy_proxy);
//    coll->get_conflicts = NULL;
}

//static char fi_algo_collection_add(struct FiAlgoCollection *self, struct FiAlgo *algo)
//{
//    if (! self || ! algo)
//        return FI_FUNC_FAIL;
//    
//    // Check that we don't have algorithm yet
//    return '\0';
//    
//}
//
//static bool fi_algo_copy_proxy(void const *src, void *dst, unsigned n)
//{
//    return false;
//}
//
//static bool fi_algo_copy(const struct FiAlgo const *src, struct FiAlgo *dst)
//{
//    return false;
//}