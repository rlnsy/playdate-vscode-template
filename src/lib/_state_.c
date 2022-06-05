#include "_state_.h"
#include "_app_const_.h"

const char *fontpath = FONT;

#ifndef TEST
void _state_init_(PlaydateAPI *pd, _App_State_ *_state_)
#else
void __real_state_init_(PlaydateAPI *pd, _App_State_ *_state_)
#endif
{
    memset(_state_, 0, sizeof(_App_State_));
    _state_->x = X0;
    _state_->y = Y0;
    _state_->dx = DX;
    _state_->dy = DY;
    const char *err;
    _state_->font = pd->graphics->loadFont(fontpath, &err);
    if (_state_->font == NULL)
    {
        pd->system->error("Couldn't load font %s: %s", fontpath, err);
    }
}