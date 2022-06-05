#ifndef __LIB_STATE__H
#define __LIB_STATE__H

#include "pd_api.h"

typedef struct
{
    LCDFont *font;
    int x;
    int y;
    int dx;
    int dy;
} _App_State_;

void _state_init_(PlaydateAPI *, _App_State_ *);
void __real_state_init_(PlaydateAPI *, _App_State_ *);
int __test_state_init_(void);

#endif