#include <stdio.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>

int _count_substring_occurence_(char *str, char *substring)
{
    int N = strlen(str);
    int M = strlen(substring);
    int n_matches = 0;
    int i = 0;
    while (i + M <= N)
    {
        if (!memcmp(str + i, substring, M))
        {
            n_matches++;
        }
        i++;
    }
    return n_matches;
}

void assert_string_contains(char *str, char *substring)
{
    // this can be optimized
    assert_true(_count_substring_occurence_(str, substring) >= 1);
}