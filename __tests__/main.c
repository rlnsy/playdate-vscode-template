#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include "_mocks_.h"
#include "pd_api.h"
#include "../src/lib/_lib_.h"
#include "../src/lib/_event_handler_.h"

static void test_init_event(void **state)
{
    // when event handler is called with init event
    _event_handler_(&__mock_PlaydateAPI, kEventInit, 0);

    // the correct font should be loaded
    LCDFont *font = __get_loaded_font_();
    assert_string_equal(font->path, "/System/Fonts/Asheville-Sans-14-Bold.pft");

    // and update function should be set
    assert_ptr_equal(__get_update_callback_(), &_update_);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_init_event),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}