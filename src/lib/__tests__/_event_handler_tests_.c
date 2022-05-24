#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>

#include "../_event_handler_.h"
#include "_util_/_mocks_.h"

void _event_handler_test_init_event(void **state)
{
    LCDFont font;

    // on init event when loadFont works properly
    will_return(__mock_graphics_loadFont, &font);
    _event_handler_(&__mock_PlaydateAPI, kEventInit, 0);

    // should set font path
    assert_string_equal(font.path, "/System/Fonts/Asheville-Sans-14-Bold.pft");

    // and update function should be set
    assert_ptr_equal(__get_update_callback_(), &_update_);
}

void _event_handler_test_init_event_error(void **state)
{
    // on init event when when loading font returns null
    will_return(__mock_graphics_loadFont, NULL);

    _event_handler_(&__mock_PlaydateAPI, kEventInit, 0);

    // should have errored
    assert_error_state("Couldn't load font");

    // update function still set
    assert_ptr_equal(__get_update_callback_(), &_update_);
}

void _update_handler_test(void **state)
{
    _update_((void *)&__mock_PlaydateAPI);
    __lcd_print(0, 0);
}