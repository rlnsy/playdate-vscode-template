#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include "_mocks_.h"
#include "pd_api.h"
#include "../_event_handler_.h"

static void test_init_event(void **state)
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

static void test_init_event_error(void **state)
{
    // on init event when when loading font returns null
    will_return(__mock_graphics_loadFont, NULL);

    _event_handler_(&__mock_PlaydateAPI, kEventInit, 0);

    // should have errored
    assert_error_state("Couldn't load font");
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_init_event),
        cmocka_unit_test(test_init_event_error),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}