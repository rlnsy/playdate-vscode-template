#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>

#include "_mock_pd_api_.h"

#include "../_app_const_.h"
#include "../_event_handler_.h"
#include "../_update_.h"
#include "../_state_.h"

typedef struct
{
    LCDFont *font_to_load;
} __Test_State_;

void _state_init_(_App_State_ *_state_)
{
    function_called();
}

void _event_handler_test_init(void **state)
{
    LCDFont font_to_load;

    expect_function_call(_state_init_);

    expect_function_call(__mock_graphics_loadFont);
    expect_string(__mock_graphics_loadFont, path, FONT);
    will_return(__mock_graphics_loadFont, &font_to_load);

    expect_function_call(__mock_system_setUpdateCallback);
    expect_value(__mock_system_setUpdateCallback, update, &_app_update_);

    _event_handler_(PD_API, kEventInit, 0);
}

void _event_handler_test_init_font_error(void **state)
{
    expect_function_call(_state_init_);

    expect_function_call(__mock_graphics_loadFont);
    expect_string(__mock_graphics_loadFont, path, FONT);
    will_return(__mock_graphics_loadFont, NULL);

    expect_function_call(__mock_system_error);

    expect_function_call(__mock_system_setUpdateCallback);
    expect_value(__mock_system_setUpdateCallback, update, &_app_update_);

    _event_handler_(PD_API, kEventInit, 0);
}

int __test_event_handler(void)
{
    const struct CMUnitTest _event_handler_tests[] = {
        cmocka_unit_test(_event_handler_test_init),
        cmocka_unit_test(_event_handler_test_init_font_error),
    };
    return cmocka_run_group_tests_name("_event_handler_", _event_handler_tests, NULL, NULL);
}