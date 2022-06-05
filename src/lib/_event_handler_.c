#include <stdio.h>
#include <stdlib.h>
#include "_device_const_.h"
#include "_app_const_.h"
#include "_state_.h"
#include "_update_.h"

const char *fontpath = FONT;

// Initial state
_App_State_ _state_;
_Update_Data_ _update_data_ = {
    ._st_ = &_state_,
};

int _event_handler_(PlaydateAPI *pd, PDSystemEvent event, uint32_t arg)
{
    const char *err;
    switch (event)
    {
    case kEventInit:
        _state_init_(&_state_);
        _state_.font = pd->graphics->loadFont(fontpath, &err);
        if (_state_.font == NULL)
            pd->system->error("Couldn't load font %s: %s", fontpath, err);
        _update_data_._pd_ = pd;
        pd->system->setUpdateCallback(_app_update_, &_update_data_);
        break;
    default:
        pd->system->logToConsole("event: %d", event);
        break;
    }

    return 0;
}