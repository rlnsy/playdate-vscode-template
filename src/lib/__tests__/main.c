#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>

#include "_mocks_.h"

#include "../_app_const_.h"
#include "../_event_handler_.h"
#include "../_update_.h"

#define PD_API (&__mock_PlaydateAPI)

LCDFont font;

void _event_handler_test_init(void **state)
{
    expect_function_call(__mock_graphics_loadFont);
    expect_string(__mock_graphics_loadFont, path, FONT);
    will_return(__mock_graphics_loadFont, &font);

    expect_function_call(__mock_system_setUpdateCallback);
    expect_value(__mock_system_setUpdateCallback, update, &_app_update_);

    _event_handler_(PD_API, kEventInit, 0);
}

void _event_handler_test_init_font_error(void **state)
{
    expect_function_call(__mock_graphics_loadFont);
    expect_string(__mock_graphics_loadFont, path, FONT);
    will_return(__mock_graphics_loadFont, NULL);

    expect_function_call(__mock_system_error);

    expect_function_call(__mock_system_setUpdateCallback);
    expect_value(__mock_system_setUpdateCallback, update, &_app_update_);

    _event_handler_(PD_API, kEventInit, 0);
}

void _app_update_test_first(void **state)
{
    // setup: do init event
    expect_function_call(__mock_graphics_loadFont);
    expect_string(__mock_graphics_loadFont, path, FONT);
    will_return(__mock_graphics_loadFont, &font);

    expect_function_call(__mock_system_setUpdateCallback);
    expect_value(__mock_system_setUpdateCallback, update, &_app_update_);

    _event_handler_(PD_API, kEventInit, 0);

    // test
    expect_function_call(__mock_graphics_clear);
    expect_value(__mock_graphics_clear, color, kColorWhite);

    expect_function_call(__mock_graphics_setFont);
    expect_value(__mock_graphics_setFont, font, &font);

    expect_function_call(__mock_graphics_drawText);
    expect_string(__mock_graphics_drawText, text, "Hello World!");
    expect_value(__mock_graphics_drawText, len, strlen("Hello World!"));
    expect_value(__mock_graphics_drawText, encoding, kASCIIEncoding);
    expect_value(__mock_graphics_drawText, x, X0);
    expect_value(__mock_graphics_drawText, y, Y0);
    will_return(__mock_graphics_drawText, 0);

    expect_function_call(__mock_system_drawFPS);
    expect_value(__mock_system_drawFPS, x, 0);
    expect_value(__mock_system_drawFPS, y, 0);

    _app_update_(PD_API);
}

int main(void)
{

    int status = 0;

    const struct CMUnitTest _event_handler_tests[] = {
        cmocka_unit_test(_event_handler_test_init),
        cmocka_unit_test(_event_handler_test_init_font_error),
    };
    status += cmocka_run_group_tests_name("_event_handler_", _event_handler_tests, NULL, NULL);

    const struct CMUnitTest _app_update_tests[] = {
        cmocka_unit_test(_app_update_test_first),
    };
    status += cmocka_run_group_tests_name("_app_update_", _app_update_tests, NULL, NULL);

    return status;
}