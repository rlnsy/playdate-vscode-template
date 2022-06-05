#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include "_mock_pd_api_.h"
#include "../_app_const_.h"
#include "../_state_.h"

void _state_init_test(void **state)
{
    _App_State_ _state_;
    LCDFont font_to_load;

    expect_function_call(__mock_graphics_loadFont);
    expect_string(__mock_graphics_loadFont, path, FONT);
    will_return(__mock_graphics_loadFont, &font_to_load);

    __real_state_init_(PD_API, &_state_);

    assert_ptr_equal(_state_.font, &font_to_load);
    assert_int_equal(_state_.dx, DX);
    assert_int_equal(_state_.dy, DY);
    assert_int_equal(_state_.x, X0);
    assert_int_equal(_state_.y, Y0);
}

void _state_init_test_font_error(void **state)
{
    _App_State_ _state_;

    expect_function_call(__mock_graphics_loadFont);
    expect_string(__mock_graphics_loadFont, path, FONT);
    will_return(__mock_graphics_loadFont, NULL);

    expect_function_call(__mock_system_error);

    __real_state_init_(PD_API, &_state_);

    assert_ptr_equal(_state_.font, NULL);
}

int __test_state_init_(void)
{
    const struct CMUnitTest _state_init_tests_[] = {
        cmocka_unit_test(_state_init_test),
        cmocka_unit_test(_state_init_test_font_error),
    };
    return cmocka_run_group_tests_name("_state_init_", _state_init_tests_, NULL, NULL);
}