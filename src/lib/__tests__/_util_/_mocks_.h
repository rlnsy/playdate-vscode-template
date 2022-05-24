#include "pd_api.h"

// mocked API
PlaydateAPI __mock_PlaydateAPI;

// Additional types spec

// no complete defintion is provided by the API, strangely
// Hence, this is not the real data structure but a mock
// in itself
struct LCDFont
{
    char *path;
    uint8_t height;
    uint8_t char_width;
};

// functions to examine the state leftover by mocks
PDCallbackFunction *__get_update_callback_();
void assert_error_state(char *errMatch);
// void __lcd_print(int _x_, int _y_, int _w_, int _h_);
void __lcd_print(int _x_, int _y_);

// exposed mock functions
LCDFont *__mock_graphics_loadFont(const char *path, const char **outErr);
void __mock_system_error(const char *fmt, ...);