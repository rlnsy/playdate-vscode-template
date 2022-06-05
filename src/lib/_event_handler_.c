#include <stdio.h>
#include <stdlib.h>
#include "_device_const_.h"
#include "_app_const_.h"
#include "_state_.h"
#include "_update_.h"

_App_State_ _state_;
_Update_Data_ _update_data_ = {
    ._st_ = &_state_,
};

int _event_handler_(PlaydateAPI *pd, PDSystemEvent event, uint32_t arg)
{
    switch (event)
    {
    case kEventInit:
        _state_init_(pd, &_state_);
        _update_data_._pd_ = pd;
        pd->system->setUpdateCallback(_app_update_, &_update_data_);
        break;
    default:
        pd->system->logToConsole("event: %d", event);
        break;
    }

    return 0;
}