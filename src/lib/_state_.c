#include "_state_.h"
#include "_app_const_.h"

#ifndef TEST
void _state_init_(_App_State_ *_state_)
#else
void __real_state_init_(_App_State_ *_state_)
#endif
{
    memset(_state_, 0, sizeof(_App_State_));
    _state_->x = X0;
    _state_->y = Y0;
    _state_->dx = DX;
    _state_->dy = DY;
}