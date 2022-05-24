#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>

#include "_event_handler_tests_.h"

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(_event_handler_test_init_event),
        cmocka_unit_test(_event_handler_test_init_event_error),
        cmocka_unit_test(_update_handler_test),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}