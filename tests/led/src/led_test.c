#include <unity.h>

#include "drivers/led.h"
#include "cmock_gpio.h"

#undef GPIO_DT_SPEC_GET
#define GPIO_DT_SPEC_GET(a,b) {}

#include "drivers/led.c"

void setUp(void)
{
}

void tearDown(void)
{
}

/*********
 * Tests
 *********/

void test_led_init_not_ready(void)
{
    int err;

    __cmock_gpio_is_ready_dt_ExpectAnyArgsAndReturn(0);
    err = led_init();
    TEST_ASSERT_EQUAL(-ENXIO, err);
}

void test_led_init_configure_error(void)
{
    int err;

    __cmock_gpio_is_ready_dt_ExpectAnyArgsAndReturn(true);
    __cmock_gpio_pin_configure_dt_ExpectAnyArgsAndReturn(-EPERM);
    err = led_init();
    TEST_ASSERT_EQUAL(-EPERM, err);
}

void test_led_init_success(void)
{
    int err;

    __cmock_gpio_is_ready_dt_ExpectAnyArgsAndReturn(true);
    __cmock_gpio_pin_configure_dt_ExpectAndReturn(&led0, GPIO_OUTPUT_ACTIVE, 0);
    err = led_init();
    TEST_ASSERT_EQUAL(0, err);
}

void test_led_set_error(void)
{
    int err;

    __cmock_gpio_pin_set_dt_ExpectAnyArgsAndReturn(-123);
    err = led_set(1);
    TEST_ASSERT_EQUAL(-123, err);
}

void test_led_set_success_on(void)
{
    int err;

    __cmock_gpio_pin_set_dt_ExpectAndReturn(&led0, 1, 0);
    err = led_set(1);
    TEST_ASSERT_EQUAL(0, err);
}

void test_led_set_success_off(void)
{
    int err;

    __cmock_gpio_pin_set_dt_ExpectAndReturn(&led0, 0, 0);
    err = led_set(0);
    TEST_ASSERT_EQUAL(0, err);
}

void test_led_toggle_error(void)
{
    int err;

    __cmock_gpio_pin_toggle_dt_ExpectAnyArgsAndReturn(-234);
    err = led_toggle();
    TEST_ASSERT_EQUAL(-234, err);
}

void test_led_toggle_success(void)
{
    int err;

    __cmock_gpio_pin_toggle_dt_ExpectAnyArgsAndReturn(0);
    err = led_toggle();
    TEST_ASSERT_EQUAL(0, err);
}

/* It is required to be added to each test. That is because unity's
 * main may return nonzero, while zephyr's main currently must
 * return 0 in all cases (other values are reserved).
 */
extern int unity_main(void);

int main(void)
{
    (void)unity_main();
    return 0;
}
