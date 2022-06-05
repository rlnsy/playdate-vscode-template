#include "pd_api.h"

#include "_app_const_.h"
#include "_state_.h"
#include "_update_.h"

#ifndef TEST
void _update_position_velocity_(_App_State_ *_state_)
#else
void __real_update_position_velocity_(_App_State_ *_state_)
#endif
{

#define _x_ (_state_->x)
#define _y_ (_state_->y)
#define _dx_ (_state_->dx)
#define _dy_ (_state_->dy)

    // _update_position_
    _x_ += _dx_;
    _y_ += _dy_;
    // _update_velocity_
    if (_x_ < 0 || _x_ > LCD_COLUMNS - TEXT_WIDTH)
        _dx_ = -_dx_;

    if (_y_ < 0 || _y_ > LCD_ROWS - TEXT_HEIGHT)
        _dy_ = -_dy_;

#undef _dy_
#undef _dx_
#undef _y_
#undef _x_
}

int _app_update_(void *userdata)
{
    _Update_Data_ *ud = userdata;

#define pd (ud->_pd_)
#define _state_ (ud->_st_)

    pd->graphics->clear(kColorWhite);
    pd->graphics->setFont(_state_->font);
    pd->graphics->drawText("Hello World!", strlen("Hello World!"), kASCIIEncoding, _state_->x, _state_->y);

    _update_position_velocity_(_state_);

    pd->system->drawFPS(0, 0);

#undef _state_
#undef pd

    return 1;
}