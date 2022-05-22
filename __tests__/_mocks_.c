#include "_mocks_.h"
#include <stdio.h>

LCDFont __loaded_font = {};

LCDFont* __mock_graphics_loadFont(const char* path, const char** outErr)
{
    __loaded_font.path = (char*) path;
    return &__loaded_font;
}

LCDFont* __get_loaded_font_()
{
    return &__loaded_font;
}

PDCallbackFunction *__update_callback = NULL;

void mock_system_setUpdateCallback(PDCallbackFunction* update, void* userdata)
{
    __update_callback = update;
}

PDCallbackFunction* __get_update_callback_()
{
    return __update_callback;
}

struct playdate_sys __mock_playdate_system = {
    .error = (void (*)(const char *, ...)) &printf,
    .setUpdateCallback = &mock_system_setUpdateCallback
};

struct playdate_graphics __mock_playdate_graphics = {
    .loadFont = &__mock_graphics_loadFont,
};

PlaydateAPI __mock_PlaydateAPI = {
    .system = &__mock_playdate_system,
    .graphics = &__mock_playdate_graphics,
};