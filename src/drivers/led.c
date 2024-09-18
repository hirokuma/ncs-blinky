#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

#include "led.h"

#define LED0 DT_ALIAS(led0)

static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0, gpios);

int led_init(void)
{
    if (!gpio_is_ready_dt(&led0)) {
        return -ENXIO;
    }

    int ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
    if (ret != 0) {
        return ret;
    }

    return 0;
}

int led_set(int onoff)
{
    int ret = gpio_pin_set_dt(&led0, onoff);
    if (ret != 0) {
        return ret;
    }
    return 0;
}

int led_toggle(void)
{
    int ret = gpio_pin_toggle_dt(&led0);
    if (ret != 0) {
        return ret;
    }
    return 0;
}
