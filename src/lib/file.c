/*
 * File:   file-array.c
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
#include <stdlib.h>
#include <malloc.h>

//#include "file.h"
//#include "util-string.h"
//
//#define fi_each_file(pArr, f)  fi_file_init( &(f) );                        \
//                                    fi_file_array_get_begin( (pArr) , &(file) ); \
//                                    while(FI_FUNC_SUCCEED == fi_file_array_get_next( (pArr) , &(f) ))
//
//const struct FiFileInfo EMPTY_FILE = {  NULL,      /* filename */
//                                        NULL,      /* file_path */
//                                        NULL,      /* file_extension */
//                                        0L,        /* size */
//                                        0,         /* file_type */
//                                       {0, 0},     /* struct timespec */
//                                       {0, NULL},  /* struct FiRef */
//                                        0          /* free_struct */
//                                    };
//
///* Prototypes */
//static unsigned short  fi_file_get_info_from_container(struct FiContainer *container,
//                                               struct FiFileInfo **ppFile);
//static void fi_file_info_ref_destory(const struct FiRef *ref);
//
///**
// * Initializes file info structure
// * @param file
// */
//void fi_file_init(struct FiFileInfo  *file)
//{
//    if (! file)
//        return;
//
//    *file = EMPTY_FILE;
//}
//
///**
// * Free the resources
// * @param file
// */
//void fi_file_destroy(struct FiFileInfo ** file)
//{
//    if (! *file)
//        return;
//
//    free((*file)->filename);
//    free((*file)->file_path);
//    free((*file)->file_extension);
//
//    if ((*file)->free_struct) {
//        printf("Freed\n\n");
//        free(*file);
//    }
//
//}
//
///**
// * Duplicates the file information
// * ** Remember to destroy copy
// * @param src
// * @param dest
// */
//void fi_file_copy(const FiFileInfo_st *src, FiFileInfo_st *dest)
//{
//    if (! src || ! dest)
//        return;
//
//    dest->filename       = fi_strndup(src->filename, strlen(src->filename));
//    dest->file_path      = fi_strndup(src->file_path, strlen(src->file_path));
//    dest->file_extension = fi_strndup(src->file_extension, strlen(src->file_extension));
//    dest->size_byte      = src->size_byte;
//    dest->modified_at    = src->modified_at;
//    dest->ref_count.free       = src->ref_count.free;
//    fi_ref_inc(&dest->ref_count);
//}
//
///**
// * Initializes the file array
// * @param array
// */
//void fi_file_array_init(struct FiFileArray * array)
//{
//    if (! array)
//        return;
//
//    fi_array_new(&array->bank);
//    
//    array->cursor = 0L;
//}
//
//void fi_file_array_destroy(struct FiFileArray *arr)
//{
//    struct FiFileInfo file;
//    fi_file_init(&file);
//    fi_file_array_get_begin(arr, &file);
//    while(FI_FUNC_SUCCEED == fi_file_array_get_next(arr, &file)) {
//        fi_ref_dec(&file.ref_count);
//    }
//    fi_array_destroy(&arr->bank);
//
//    arr->cursor = 0L;
//}
//
//static unsigned short  fi_file_get_info_from_container(struct FiContainer *container,
//                                            struct FiFileInfo **ppFile)
//{
//    if (! container || ! container->data)
//        return FI_FUNC_FAIL;
//
//    (*ppFile)->ref_count.free = fi_file_info_ref_destory;
//    fi_ref_inc(&(*ppFile)->ref_count);
//    
//    return FI_FUNC_SUCCEED;
//    
//}
//
//static void fi_file_info_ref_destory(const struct FiRef *ref)
//{
//    struct FiFileInfo *pInfo = container_of(ref, struct FiFileInfo, ref_count);
//    
//    if (! pInfo)
//        return;
//    
//    fi_file_destroy(&pInfo);
//}
//
///**
// * @param arr
// * @param info
// * @return 
// */
//int fi_file_array_add_file_info(struct FiFileArray *arr,
//                                struct FiFileInfo *info)
//{
//    if (! info || ! arr)
//        return FI_FUNC_FAIL;
//
//    fi_array_push(&arr->bank, info, sizeof *info);
//    
//    return FI_FUNC_SUCCEED;
//}
//
//
//unsigned fi_file_array_get_size(struct FiFileArray *arr)
//{
//    return arr->bank.len;
//}
//
///* ------------------------------------------------------------------
// * ------------------------------------------------------------------
// * Traversing
// */
//
///**
// * Returns File Info structure
// * 
// * return value must be freed with "fi_file_info_value_cleanup" !
// * @param arr
// * @param i
// * @return FileInfo
// */
//unsigned short fi_file_array_get_at(struct FiFileArray *arr, 
//                          unsigned long i, struct FiFileInfo *pInfo)
//{
//
//    struct FiContainer *pCon = fi_array_get(&arr->bank, i);
//    unsigned short ret = fi_file_get_info_from_container(pCon, &pInfo);
//
//    fi_ref_dec(&pCon->ref_count); // Free the resource
//
//    return ret;
//}
//
//unsigned short fi_file_array_get_begin(struct FiFileArray *arr, struct FiFileInfo *file)
//{
//    arr->cursor = 0L;
//    
//    return fi_file_array_get_at(arr, arr->cursor, file);
//}
//
//
//unsigned short fi_file_array_get_next(struct FiFileArray *arr, struct FiFileInfo *file)
//{
//    if (arr->bank.len <= (arr->cursor + 1))
//        return FI_FUNC_FAIL;
//    
//    return fi_file_array_get_at(arr, ++arr->cursor, file);    
//}
//
//unsigned short fi_file_array_get_end(struct FiFileArray *arr, struct FiFileInfo *file)
//{
//    unsigned short ret = FI_FUNC_FAIL;
//    if ((arr->bank.len -1) > -1) {
//        ret = fi_file_array_get_at(arr, arr->bank.len - 1, file);
//    }
//    
//    return ret;
//}
//
