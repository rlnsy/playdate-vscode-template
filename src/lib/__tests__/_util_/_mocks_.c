#include "_mocks_.h"
#include <stdio.h>
#include <stdarg.h>
#include <signal.h>
#include <setjmp.h>
#include <cmocka.h>
#include <assert.h>
#include "_util_.h"
#include "../../_device_const_.h"

LCDFont *__mock_graphics_loadFont(const char *path, const char **outErr)
{
    LCDFont *font = (LCDFont *)mock();
    if (font != NULL)
    {
        font->path = (char *)path;
    }
    return font;
}

LCDFont *__mock_current_font;

void __mock_graphics_setFont(LCDFont *font)
{
    __mock_current_font = font;
}

// Mock LCD represents the state of the display with bit encoding
// for pixel value, row major order
#define __LCD_WHITE 0b00000000
#define __LCD_BLACK 0b00000001
uint8_t __lcd[PD_SCREEN_HEIGHT][PD_SCREEN_WIDTH / 8];

#define __LCD_SIZE (PD_SCREEN_HEIGHT * PD_SCREEN_WIDTH)
#define __LCD_SIZE_BYTES (__LCD_SIZE / 8)

uint8_t __lcd_bit_map[8] = {
    0b10000000,
    0b01000000,
    0b00100000,
    0b00010000,
    0b00001000,
    0b00000100,
    0b00000010,
    0b00000001,
};

#define CHECK_COORDS                                          \
    if (_y_ >= PD_SCREEN_HEIGHT || _x_ >= PD_SCREEN_WIDTH)    \
    {                                                         \
        __mock_system_error(                                  \
            "invalid screen coordinates: (%d,%d)", _x_, _y_); \
    }

uint8_t __lcd_value(int _x_, int _y_)
{
    CHECK_COORDS
    return __lcd[_y_][_x_ / 8] & __lcd_bit_map[_x_ % 8];
}

void __lcd_set(int _x_, int _y_, uint8_t value)
{
    CHECK_COORDS
    __lcd[_y_][_x_ / 8] |= (value << (7 - (_x_ % 8)));
}

char *__LCD_PRINT_WHITE = "***";
char *__LCD_PRINT_BLACK = "   ";

// this can be used for debugging
// TODO: recommended to constrain the region such that it fits within the terminal bounds
void __lcd_print(int _x_, int _y_)
{
    FILE *f = fopen("./.temp/pd_lcd", "a");
    fprintf(f, "===PRINT LCD===\n");
    for (int _i_ = 0; _i_ < PD_SCREEN_HEIGHT; _i_++)
    {
        for (int _j_ = 0; _j_ < PD_SCREEN_WIDTH; _j_++)
        {
            fprintf(f, "%s", __lcd_value(_j_, _i_) ? __LCD_PRINT_BLACK : __LCD_PRINT_WHITE);
        }
        fprintf(f, "%s", "\n");
    }
    fclose(f);
}

void __mock_graphics_clear(LCDColor color)
{
    //  can only set to white
    memset(__lcd, __LCD_WHITE, __LCD_SIZE_BYTES);
}

uint8_t __mock_graphics_getFontHeight(LCDFont *font)
{
    return font->height;
}

int __mock_graphics_drawText(const void *text, size_t len, PDStringEncoding encoding, int x, int y)
{
    return 0;
}

void __mock_system_drawFPS(int x, int y)
{
    for (int _x_ = 2; _x_ < 28; _x_++)
    {
        for (int _y_ = 2; _y_ < 22; _y_++)
        {
            __lcd_set(_x_, _y_, __LCD_BLACK);
        }
    }
    return;
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
    .setUpdateCallback = &mock_system_setUpdateCallback,
    .drawFPS = &__mock_system_drawFPS};

struct playdate_graphics __mock_playdate_graphics = {
    .loadFont = &__mock_graphics_loadFont,
    .getFontHeight = &__mock_graphics_getFontHeight,
    .setFont = &__mock_graphics_setFont,
    .clear = &__mock_graphics_clear,
    .drawText = &__mock_graphics_drawText,
};

PlaydateAPI __mock_PlaydateAPI = {
    .system = &__mock_playdate_system,
    .graphics = &__mock_playdate_graphics,
};