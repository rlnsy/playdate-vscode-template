#include "_mocks_.h"
#include <stdio.h>
#include <stdarg.h>
#include <signal.h>
#include <setjmp.h>
#include <cmocka.h>
#include <assert.h>
#include "_util_.h"

LCDFont *__mock_graphics_loadFont(const char *path, const char **outErr)
{
    LCDFont *font = (LCDFont *)mock();
    if (font != NULL)
    {
        font->path = (char *)path;
    }
    return font;
}

PDCallbackFunction *__update_callback = NULL;

void mock_system_setUpdateCallback(PDCallbackFunction *update, void *userdata)
{
    __update_callback = update;
}

PDCallbackFunction *__get_update_callback_()
{
    return __update_callback;
}

int __mock_errState = 0;
#define __MOCK_ERRBUF_LEN 256 // max error message len + 1
char __mock_errBuf[__MOCK_ERRBUF_LEN];

void __mock_system_error(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    // fprintf(stderr, fmt, args);
    int errLen = sprintf(__mock_errBuf, fmt, args);
    __mock_errBuf[errLen] = 0; // terminate string
    va_end(args);
    __mock_errState = 1;
}

void assert_error_state(char *errMatch)
{
    int tmp = __mock_errState;
    __mock_errState = 0; // reset
    assert_int_equal(tmp, 1);
    assert_string_contains(__mock_errBuf, errMatch);
}

struct playdate_sys __mock_playdate_system = {
    .error = (void (*)(const char *, ...)) & __mock_system_error,
    .setUpdateCallback = &mock_system_setUpdateCallback};

struct playdate_graphics __mock_playdate_graphics = {
    .loadFont = &__mock_graphics_loadFont,
};

PlaydateAPI __mock_PlaydateAPI = {
    .system = &__mock_playdate_system,
    .graphics = &__mock_playdate_graphics,
};