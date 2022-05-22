#include "pd_api.h"

// mocked API
PlaydateAPI __mock_PlaydateAPI;

// Additional types spec

// no complete defintion is provided by the API, strangely
struct LCDFont {
    char *path;
};

// functions to examine the state leftover by mocks
PDCallbackFunction* __get_update_callback_();
LCDFont* __get_loaded_font_();