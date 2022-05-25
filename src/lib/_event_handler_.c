//
//  Implementations of main event handler and update function
//  Created by Dave Hayden on 7/30/14.
//  Copyright (c) 2014 Panic, Inc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "_event_handler_.h"
#include "_device_const_.h"
#include "_app_const_.h"

const char *fontpath = FONT;
LCDFont *font = NULL;

int _event_handler_(PlaydateAPI *pd, PDSystemEvent event, uint32_t arg)
{
    (void)arg; // arg is currently only used for event = kEventKeyPressed

    if (event == kEventInit)
    {
        const char *err;
        font = pd->graphics->loadFont(fontpath, &err);

        if (font == NULL)
            pd->system->error("%s:%i Couldn't load font %s: %s", __FILE__, __LINE__, fontpath, err);

        // Note: If you set an update callback in the kEventInit handler, the system assumes the game is pure C and doesn't run any Lua code in the game
        pd->system->setUpdateCallback(_update_, pd);
    }

    return 0;
}

int x = X0;
int y = Y0;
int dx = DX;
int dy = DY;

int _update_(void *userdata)
{
    PlaydateAPI *pd = userdata;

    pd->graphics->clear(kColorWhite);
    pd->graphics->setFont(font);
    pd->graphics->drawText("Hello World!", strlen("Hello World!"), kASCIIEncoding, x, y);

    x += dx;
    y += dy;

    if (x < 0 || x > LCD_COLUMNS - TEXT_WIDTH)
        dx = -dx;

    if (y < 0 || y > LCD_ROWS - TEXT_HEIGHT)
        dy = -dy;

    pd->system->drawFPS(0, 0);

    return 1;
}