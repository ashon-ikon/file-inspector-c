/* 
 * File:   test-conjoined-string.c
 * Author: Yinka Ashon
 * 
 * Copyright (c) 2018 Yinka Ashon
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
 */
#include "test-conjoined-string.h"

FI_TEST_RESULT test_hi_string_empty()
{
        struct FiHiStringBank *b = fi_conj_string_new();
        
        fi_conj_string_free(b);
        
        return FI_TEST_OKAY;
}

FI_TEST_RESULT test_hi_string_will_add_successfully()
{
        struct FiHiStringBank *b = fi_conj_string_new();
        struct FiHiString str;
        
        const char *test_str = "This is so awesome ! ";
        
        fi_conj_string_add(b, test_str, &str);
        
        fi_return_fail_if_not(fi_strcmp0(test_str, FI_STR_ADDR(&str)),
                              fi_make_msg("Wrong string stored %s",
                                          FI_STR_ADDR(&str)));
        fi_conj_string_free(b);
        
        return FI_TEST_OKAY;
}

FI_TEST_RESULT test_hi_string_will_add_multiple_strings_successfully()
{
        struct FiHiStringBank *b = fi_conj_string_new();
        
        const char *test_strs[] = {
                "This is so awesome ! ",
                "Oh yeah :)",
                "Incredible<>",
                "1"
        };
        
        unsigned char total = 4;
        struct FiHiString str[total];
        
        unsigned char i = 0; 
        for (i = 0; i < total; i++) {
                fi_conj_string_add(b, test_strs[i], &str[i]);
        }
        
        for (i =0; i < total; i++) {                
                fi_return_fail_if_not(fi_strcmp0(test_strs[i],
                                FI_STR_ADDR(&str[i])),
                                fi_make_msg("Wrong string stored %s",
                                            FI_STR_ADDR(&str[i])));
        }
        
        fi_conj_string_free(b);
        
        return FI_TEST_OKAY;
}

FI_TEST_RESULT test_hi_string_will_reuse_last_slot_after_removal()
{
        struct FiHiStringBank *b = fi_conj_string_new();
        
        const char *test_strs[] = {
                "Lorem",
                "Ipsum",
                "situr",
                "De 'lamor"
        };
        
        unsigned char total = 4;
        struct FiHiString str[total];
        
        unsigned char i = 0; 
        for (i = 0; i < total; i++) {
                fi_conj_string_add(b, test_strs[i], &str[i]);
        }
        
        fi_conj_string_remove_last(b);
        fi_conj_string_remove_last(b);
        struct FiHiString new_str;
        const char *new_s = "This is so much fun!!!";
        fi_conj_string_add(b, new_s, &new_str);
        fi_return_fail_if_not(fi_strcmp0(new_s, FI_STR_ADDR(&new_str)),
                        fi_make_msg("Last string does not match. Got `%s´",
                                    FI_STR_ADDR(&new_str)));
        
        fi_conj_string_free(b);
        
        return FI_TEST_OKAY;
}

FI_TEST_RESULT test_hi_string_will_remove_last_string_successfully()
{
        struct FiHiStringBank *b = fi_conj_string_new();
        
        const char *test_strs[] = {
                "Lorem",
                "Ipsum",
                "situr",
                "De 'lamor"
        };
        
        unsigned char total = 4;
        struct FiHiString str[total];
        
        unsigned char i = 0; 
        for (i = 0; i < total; i++) {
                fi_conj_string_add(b, test_strs[i], &str[i]);
        }
        
        fi_conj_string_remove_last(b);        
        fi_return_fail_if_not(fi_strcmp0("", FI_STR_ADDR(&str[total - 1])),
                        fi_make_msg("String no # %d should be NULL, got `%s´",
                                    total - 1, FI_STR_ADDR(&str[total - 1])));
        
        fi_conj_string_remove_last(b);        
        fi_return_fail_if_not(fi_strcmp0("", FI_STR_ADDR(&str[total - 2])),
                        fi_make_msg("String no # %d should be NULL, got `%s´",
                                    total - 2, FI_STR_ADDR(&str[total - 2])));
        
        fi_conj_string_free(b);
        
        return FI_TEST_OKAY;
}

FI_TEST_RESULT test_hi_string_will_return_null_when_empty()
{
        struct FiHiStringBank *b = fi_conj_string_new();
        struct FiHiString str;
        
        const char *test_str = "This is so awesome ! ";
        
        fi_conj_string_add(b, test_str, &str);
        fi_conj_string_wipe_content(b);
        fi_return_fail_if_not(NULL == FI_STR_ADDR(&str),
                              fi_make_msg("Failed to empty string %s",
                                          FI_STR_ADDR(&str)));
        fi_conj_string_free(b);
        
        return FI_TEST_OKAY;
}

FI_TEST_RESULT test_hi_string_will_return_null_when_quickly_emptied()
{
        struct FiHiStringBank *b = fi_conj_string_new();
        struct FiHiString str;
        
        const char *test_str = "This is so awesome ! ";
        
        fi_conj_string_add(b, test_str, &str);
        fi_conj_string_wipe_content_quick(b);
        fi_return_fail_if_not(NULL == FI_STR_ADDR(&str),
                              fi_make_msg("Failed to empty string %s",
                                          FI_STR_ADDR(&str)));
        fi_conj_string_free(b);
        
        return FI_TEST_OKAY;
}

int main()
{
    FiTestFunc fi_tests [] = {
        FI_TEST_ENTRY(test_hi_string_empty),
        FI_TEST_ENTRY(test_hi_string_will_add_successfully),
        FI_TEST_ENTRY(test_hi_string_will_add_multiple_strings_successfully),
        FI_TEST_ENTRY(test_hi_string_will_remove_last_string_successfully),
        FI_TEST_ENTRY(test_hi_string_will_return_null_when_empty),
        FI_TEST_ENTRY(test_hi_string_will_return_null_when_quickly_emptied),
        FI_TEST_ENTRY_END
    };
    
    return run(fi_tests);
}