#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include "../_app_const_.h"
#include "../_state_.h"

void _state_init_test(void **state)
{
    _App_State_ _state_;
    __real_state_init_(&_state_);
    assert_ptr_equal(_state_.font, NULL);
    assert_int_equal(_state_.dx, DX);
    assert_int_equal(_state_.dy, DY);
    assert_int_equal(_state_.x, X0);
    assert_int_equal(_state_.y, Y0);
}

int __test_state_init_(void)
{
    const struct CMUnitTest _state_init_tests_[] = {
        cmocka_unit_test(_state_init_test),
    };
    return cmocka_run_group_tests_name("_state_init_", _state_init_tests_, NULL, NULL);
}