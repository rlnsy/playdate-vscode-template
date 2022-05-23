#include "pd_api.h"

// mocked API
PlaydateAPI __mock_PlaydateAPI;

// Additional types spec

// no complete defintion is provided by the API, strangely
struct LCDFont
{
    char *path;
};

// functions to examine the state leftover by mocks
PDCallbackFunction *__get_update_callback_();
void assert_error_state(char *errMatch);

// exposed mock functions
LCDFont *__mock_graphics_loadFont(const char *path, const char **outErr);