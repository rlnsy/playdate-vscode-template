#ifndef __LIB_UPDATE__H
#define __LIB_UPDATE__H

#include "_state_.h"

typedef struct
{
    PlaydateAPI *_pd_;
    _App_State_ *_st_;
} _Update_Data_;

int _app_update_(void *); // accepts _Update_Data_
int __test_app_update(void);
void _update_position_velocity_(_App_State_ *);
void __real_update_position_velocity_(_App_State_ *);
int __test_update_position_velocity(void);

#endif